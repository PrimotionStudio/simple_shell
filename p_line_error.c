#include "prime.h"

/**
 * p_line_error: handle error if line could not be read
 * @p_read_bytes: The bytes to read
 * @p_line: THe full line
 */
void p_line_error(int p_read_bytes, char *p_line)
{
	if (p_read_bytes == -1)
	{
		if (feof(stdin))
		{
			printer("\n");
			free(p_line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			free(p_line);
			exit(EXIT_FAILURE);
		}
	}
}
