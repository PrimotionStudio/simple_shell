#include "prime.h"

/**
 * p_shell - custome shell loop
 * @p_info: the info structur
 * @av: the argv
 * Return: 0, 1
 */
int p_shell(info_t *p_info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		p_clear_info(p_info);
		if (p_interact(p_info))
			_puts("$ ");
		p_eputchar(P_BUFFER_FLUSH);
		r = p_get_input(p_info);
		if (r != -1)
		{
			p_set_info(p_info, av);
			builtin_ret = p_get_builtin(p_info);
			if (builtin_ret == -1)
				p_get_cmd(p_info);
		}
		else if (p_interact(p_info))
			_putchar('\n');
		p_free_info(p_info, 0);
	}
	p_write_history(p_info);
	p_free_info(p_info, 1);
	if (!p_interact(p_info) && p_info->status)
		exit(p_info->status);
	if (builtin_ret == -2)
	{
		if (p_info->err_num == -1)
			exit(p_info->status);
		exit(p_info->err_num);
	}
	return (builtin_ret);
}

/**
 * p_get_builtin - gets a builtin command
 * @p_info: the info structuer
 * Return: -1, 0, 1, 2
 */
int p_get_builtin(info_t *p_info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", p_exit},
		{"env", p_env},
		{"help", p_help},
		{"history", p_history},
		{"setenv", p_setenv},
		{"unsetenv", p_unsetenv},
		{"cd", p_cd},
		{"alias", p_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(p_info->argv[0], builtintbl[i].type) == 0)
		{
			p_info->line_count++;
			built_in_ret = builtintbl[i].func(p_info);
			break;
		}
	return (built_in_ret);
}

/**
 * p_get_cmd - finds a path for a command
 * @p_info: info structure
 * Return: void
 */
void p_get_cmd(info_t *p_info)
{
	char *path = NULL;
	int i, k;

	p_info->path = p_info->argv[0];
	if (p_info->linecount_flag == 1)
	{
		p_info->line_count++;
		p_info->linecount_flag = 0;
	}
	for (i = 0, k = 0; p_info->arg[i]; i++)
		if (!p_isdelim(p_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = p_get_path(p_info, p_getenv(p_info, "PATH="), p_info->argv[0]);
	if (path)
	{
		p_info->path = path;
		p_fork_cmd(p_info);
	}
	else
	{
		if ((p_interact(p_info) || p_getenv(p_info, "PATH=")
					|| p_info->argv[0][0] == '/') && p_is_cmd(p_info, p_info->argv[0]))
			p_fork_cmd(p_info);
		else if (*(p_info->arg) != '\n')
		{
			p_info->status = 127;
			print_error(p_info, "not found\n");
		}
	}
}

/**
 * p_fork_cmd - Starts shild process
 * @p_info: info structure
 */
void p_fork_cmd(info_t *p_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(p_info->path, p_info->argv, p__getenv(p_info)) == -1)
		{
			p_free_info(p_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(p_info->status));
		if (WIFEXITED(p_info->status))
		{
			p_info->status = WEXITSTATUS(p_info->status);
			if (p_info->status == 126)
				print_error(p_info, "Permission denied\n");
		}
	}
}
