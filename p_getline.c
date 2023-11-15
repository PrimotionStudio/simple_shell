#include "prime.h"

/**
 * read_buffer - Used to read the buffer
 * @buffer: The buffer
 * @buffer_size: the size of the buffer
 * @fd: The file
 * Return: the chars read
 */
ssize_t read_buffer(char *buffer, size_t buffer_size, FILE *fd)
{
	ssize_t chars_read = read(fileno(fd), buffer, buffer_size);

	if (chars_read == 0)
		return (-1);
	else if (chars_read == (ssize_t)-1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	return (chars_read);
}

/**
  * extract_line - Extract the line
  * @lineptr: the line
  * @n: the size
  * @buffer: The buffer
  * @start: the start
  * @end: The end
  * Return: The size
  */
ssize_t extract_line(char **lineptr, size_t *n,
		char *buffer, size_t start, size_t end)
{
	size_t line_index = 0, j = 0;
	char *line;

	line = (char *)malloc(end - start + 1);
	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (j = start; j < end; j++)
		line[line_index++] = buffer[j];
	line[end - start] = '\0';
	*lineptr = line;
	*n = end - start + 1;
	return (end - start);
}

/**
 * _getline - Replica of the get line
 * @lineptr: The line
 * @n: The size
 * @fd: The File
 * Return: 0
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *fd)
{
	size_t i = 0, chars_read = 0, buffer_index = 0;
	char buffer[BUFFER_SIZE];
	int newline_found = 0;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	while (1)
	{
		if (buffer_index >= chars_read)
		{
			chars_read = read_buffer(buffer, BUFFER_SIZE, fd);
			buffer_index = 0;
		}
		for (; buffer_index < chars_read; ++buffer_index)
		{
			if (buffer[buffer_index] == '\n')
			{
				newline_found = 1;
				buffer_index++;
				break;
			}
			i++;
		}
		if (newline_found)
			return (extract_line(lineptr, n, buffer,
						buffer_index - i - 1, buffer_index));
	}
}
