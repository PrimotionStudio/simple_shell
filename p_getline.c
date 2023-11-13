#include "prime.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *fd)
{
	size_t i = 0, line_index = 0, j = 0, chars_read = 0, buffer_index = 0;
	char *line = NULL, buffer[BUFFER_SIZE];
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
			buffer_index = 0;
			chars_read = read(fileno(fd), buffer, BUFFER_SIZE);
			if (chars_read == 0)
			{
				if (line)
					free(line);
				return (-1);
			}
			else if (chars_read == (size_t)-1)
			{
				perror("read");
				if (line)
					free(line);
				exit(EXIT_FAILURE);
			}
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
		{
			line = (char *)malloc(i + 1);
			if (line == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			line_index = 0;
			for (j = buffer_index - i - 1; j < buffer_index; j++)
				line[line_index++] = buffer[j];
			line[i] = '\0';

			*lineptr = line;
			*n = i + 1;

			return (i);
		}
	}
}
