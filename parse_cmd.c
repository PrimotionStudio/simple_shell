#include "prime.h"

/**
 * parse_cmd - Parses the input command line into individual arguments
 * @p_line: The input command line string
 * Return: An array of strings containing individual arguments.
 *         NULL on failure.
 * Description: Tokenizes the input line using space as the delimiter.
 *              Allocates memory for arguments and copies tokens.
 */
char **parse_cmd(char *p_line)
{
	char **p_args = NULL;
	char *p_token = NULL;
	size_t p = 0;

	p_args = malloc(sizeof(char *) * 64);
	if (p_args == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	p_token = strtok(p_line, " ");
	while (p_token != NULL)
	{
		p_args[p] = strdup(p_token);
		if (p_args[p] == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		p_token = strtok(NULL, " ");
		p++;
	}
	p_args[p] = NULL;
	return (p_args);
}
