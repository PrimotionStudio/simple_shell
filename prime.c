#include "prime.h"

/**
 * main - Entry point of the shell program
 * Return: Always returns 0
 * Description: Displays a prompt, reads user input,
 *		parses and executes commands.
 */
int main(void)
{
	char *p_line = NULL, **p_args;
	size_t p_linesize = 0;
	ssize_t p_read_bytes;

	signal(SIGINT, p_ctrlc);
	while (1)
	{
		printer("$ ");
		p_read_bytes = getline(&p_line, &p_linesize, stdin);
		p_line_error(p_read_bytes, p_line);
		p_line[strcspn(p_line, "\n")] = '\0';
		if (p_line[0] != '\0')
		{
			p_args = parse_cmd(p_line);
			if (p_args)
			{
				if (strcmp(p_args[0], "exit") == 0)
					p_exit();
				else if (strcmp(p_args[0], "env") == 0)
					p_env();
				else
					p_exec(p_args);
				free(p_args);
			}
		}
		free(p_line);
		p_line = NULL;
		p_linesize = 0;
	}
	return (0);
}
