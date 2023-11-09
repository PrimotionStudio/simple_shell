#include "prime.h"

/**
 * p_exec - Executes the given command with arguments
 * @p_args: An array of strings containing the command and its arguments
 * Description: Forks a child process to execute the specified command.
 *              Handles command execution and error messages.
 */
void p_exec(char **p_args)
{
	pid_t pid;
	int p_status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(p_args[0], p_args) == -1)
		{
			perror(p_args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &p_status, 0);
	}
}
