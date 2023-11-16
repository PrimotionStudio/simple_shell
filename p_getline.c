#include "prime.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, p_ctrlc);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = p_getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			p_comment(*buf);
			p_build_history(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * p_get_input - gets a whole line
 * @p_args: structure
 * Return: bytes
 */
ssize_t p_get_input(info_t *p_args)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t p_bytes = 0;
	char **p_buf = &(p_args->arg), *p;

	_putchar(BUF_FLUSH);
	p_bytes = input_buf(p_args, &buffer, &len);
	if (p_bytes == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		p_check_chain(p_args, buffer, &j, i, len);
		while (j < len)
		{
			if (p_is_chain(p_args, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			p_args->cmd_buf_type = CMD_NORM;
		}

		*p_buf = p;
		return (_strlen(p));
	}

	*p_buf = buffer;
	return (p_bytes);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * p_getline - gets line of commands from stdin
 * @p_args: structure
 * @pointer: pointer or NULL
 * @length: length of buffer
 * Return: the size of line read
 */
int p_getline(info_t *p_args, char **pointer, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, size = 0;
	char *p = NULL, *p_new = NULL, *str;

	p = *pointer;
	if (p && length)
		size = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(p_args, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	str = _strchr(buffer + i, '\n');
	k = str ? 1 + (unsigned int)(str - buffer) : len;
	p_new = _realloc(p, size, size ? size + k : k + 1);
	if (!p_new)
		return (p ? free(p), -1 : -1);
	if (size)
		_strncat(p_new, buffer + i, k - i);
	else
		_strncpy(p_new, buffer + i, k - i + 1);
	size += k - i;
	i = k;
	p = p_new;
	if (length)
		*length = size;
	*pointer = p;
	return (size);
}

/**
 * p_ctrlc - handles CTRL + C gracefully
 * @si: the signal
 */
void p_ctrlc(__attribute__((unused))int si)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
