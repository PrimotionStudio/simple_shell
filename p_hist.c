#include "prime.h"

/**
 * p_get_history - gets history
 * @p_args: argument
 * Return: history
 */
char *p_get_history(info_t *p_args)
{
	char *p_buf, *p_dir;

	p_dir = p_getenv(p_args, "HOME=");
	if (!p_dir)
		return (NULL);
	p_buf = malloc(sizeof(char) * (_strlen(p_dir) + _strlen(HIST_FILE) + 2));
	if (!p_buf)
		return (NULL);
	p_buf[0] = 0;
	_strcpy(p_buf, p_dir);
	_strcat(p_buf, "/");
	_strcat(p_buf, HIST_FILE);
	return (p_buf);
}

/**
 * p_write_history - append a command to the hsitory file
 * @p_args: argument
 * Return: 1, -1
 */
int p_write_history(info_t *p_args)
{
	ssize_t fd;
	char *filen = p_get_history(p_args);
	list_t *new = NULL;

	if (!filen)
		return (-1);

	fd = open(filen, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filen);
	if (fd == -1)
		return (-1);
	for (new = p_args->history; new; new = new->next)
	{
		p_putsfiled(new->str, fd);
		p_putfiled('\n', fd);
	}
	p_putfiled(P_BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * p_read_history - get history
 * @p_args: argument
 * Return: count or 0
 */
int p_read_history(info_t *p_args)
{
	int i, last = 0, p_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *p_buf = NULL, *filen = p_get_history(p_args);

	if (!filen)
		return (0);

	fd = open(filen, O_RDONLY);
	free(filen);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	p_buf = malloc(sizeof(char) * (fsize + 1));
	if (!p_buf)
		return (0);
	rdlen = read(fd, p_buf, fsize);
	p_buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(p_buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (p_buf[i] == '\n')
		{
			p_buf[i] = 0;
			p_build_history(p_args, p_buf + last, p_count++);
			last = i + 1;
		}
	if (last != i)
		p_build_history(p_args, p_buf + last, p_count++);
	free(p_buf);
	p_args->histcount = p_count;
	while (p_args->histcount-- >= HIST_MAX)
		p_delete_node(&(p_args->history), 0);
	p_reno_history(p_args);
	return (p_args->histcount);
}

/**
 * p_build_history - Append to the history
 * @p_args: argument
 * @p_buffer: buffer
 * @p_count: the numbering
 * Return: 0
 */
int p_build_history(info_t *p_args, char *p_buffer, int p_count)
{
	list_t *new = NULL;

	if (p_args->history)
		new = p_args->history;
	p_add_node_end(&new, p_buffer, p_count);

	if (!p_args->history)
		p_args->history = new;
	return (0);
}

/**
 * p_reno_history - reno history
 * @p_args: arguments
 * Return: the new numbering
 */
int p_reno_history(info_t *p_args)
{
	list_t *new = p_args->history;
	int p = 0;

	while (new)
	{
		new->num = p++;
		new = new->next;
	}
	return (p_args->histcount = p);
}
