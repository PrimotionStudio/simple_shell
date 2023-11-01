#include "shell.h"

/**
 * main - Entry point to simple shell project
 * @ac: number of arguments parsed
 * @av: an arry of arguments parsed
 * @en: an array of environmental variables
 * Return: 0
 */
int main(int ac, char **av, char *en[])
{
	char *cmd = NULL;
	size_t cmdsize = 0;
	char *args[2];
	pid_t child_pid;
	int pid_status;

	(void)ac;
	(void)av;
	(void)en;
	while (1)
	{
		printf("OurShell $ ");
		if (getline(&cmd, &cmdsize, stdin) == -1)
		{
			printf("\n");
			free(cmd);
			return (0);
		}
		cmd[strcspn(cmd, "\n")] = '\0';
		args[0] = cmd;
		args[1] = NULL;
		child_pid = fork();
		if (child_pid == -1)
		{
			printf("%s: No such file or directory\n", av[0]);
		}
		if (child_pid == 0)
		{
			if (execve(cmd, args, NULL) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
			}
		}
		else
		{
			waitpid(child_pid, &pid_status, 0);
		}
	}
	free(cmd);
	return (0);
}
