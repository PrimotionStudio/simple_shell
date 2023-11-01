#include "shell.h"

int main(int ac, char **av, char *en[])
{
	char *cmd = NULL;
	size_t cmdsize = 0;
	char *args[2];
	
	(void)ac;
	(void)av;
	(void)en;

	while (1)
	{
		printf("OurShell $ " );
		if (getline(&cmd, &cmdsize, stdin) == -1)
		{
			printf("\n");
			free(cmd);
			return (0);
		}
		cmd[strcspn(cmd, "\n")] = '\0';
		args[0] = cmd;
		args[1] = NULL;
		if (execve(cmd, args, NULL) == -1)
		{
			printf("%s: No such file or directory\n", av[0]);
		}
		else
		{
			continue;
		}
	}
	return (0);
}
