#include "prime.h"

int main(int ac, char **av, char **en)
{
	char *p_line = NULL, *p_linecpy = NULL, *token = NULL, **p_args;
	size_t p_linesize = 0/*, p_notoken = 0*/, p_len = 0, p, pp, nocommand = 0;

	signal(SIGINT, p_ctrlc);
	(void)ac, (void)av, (void)en;
	while (1)
	{
		printf("$ ");
		if (getline(&p_line, &p_linesize, stdin) == -1)
		{
			write(1, "\n", STDOUT_FILENO);
			exit(EXIT_FAILURE);
		}
		p_line[strcspn(p_line, "\n")] = '\0';
		p_len = _strlen(p_line);
		p_linecpy = (char *)malloc(p_len + 1);
		if (p_linecpy == NULL)
			exit(EXIT_FAILURE);
		for (p = 0; p < p_len; p++)
			p_linecpy[p] = p_line[p];

		/* Tokenize */
		/* To set the tokens into the args */
		p_args = (char **)malloc(sizeof(char *) * p_len);
		if (p_args == NULL)
			exit(EXIT_FAILURE);
		p = 0;
		token = strtok(p_linecpy, " ");
		while (token)
		{
			p_args[p] = (char *)malloc(_strlen(token) + 1);
			if (p_args[p] == NULL)
				exit(EXIT_FAILURE);
			p_len = 0;
			p_len = _strlen(p_line);
			for (pp = 0; pp < p_len; pp++)
				p_args[p][pp] = token[pp];
			token = strtok(NULL, " ");
			p++;
		}
		printer(p_args[0]);
		printer("\n");

		free(p_linecpy);
		for (p = 0; p < p_len; p++)
			free(p_args[p]);
		free(p_args);
	}
	return (0);
}