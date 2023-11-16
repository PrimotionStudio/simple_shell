#include "prime.h"

/**
 * p_exit - the exit command
 * @p_args: arguments
 * Return: 0
 */
int p_exit(info_t *p_args)
{
	int e_check;

	if (p_args->argv[1])
	{
		e_check = p_atoi_error(p_args->argv[1]);
		if (e_check == -1)
		{
			p_args->status = 2;
			print_error(p_args, "Illegal number: ");
			p_eputs(p_args->argv[1]);
			p_eputchar('\n');
			return (1);
		}
		p_args->err_num = p_atoi_error(p_args->argv[1]);
		return (-2);
	}
	p_args->err_num = -1;
	return (-2);
}

/**
 * p_cd - change directory
 * @p_args: arguments
 * Return: 0
 */
int p_cd(info_t *p_args)
{
	char *p_str, *p_dir, p_buffer[1024];
	int p_ret;

	p_str = getcwd(p_buffer, 1024);
	if (!p_str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!p_args->argv[1])
	{
		p_dir = p_getenv(p_args, "HOME=");
		if (!p_dir)
			p_ret = chdir((p_dir = p_getenv(p_args, "PWD=")) ? p_dir : "/");
		else
			p_ret = chdir(p_dir);
	}
	else if (_strcmp(p_args->argv[1], "-") == 0)
	{
		if (!p_getenv(p_args, "OLDPWD="))
		{
			_puts(p_str);
			_putchar('\n');
			return (1);
		}
		_puts(p_getenv(p_args, "OLDPWD=")), _putchar('\n');
		p_ret = chdir((p_dir = p_getenv(p_args, "OLDPWD=")) ? p_dir : "/");
	}
	else
		p_ret = chdir(p_args->argv[1]);
	if (p_ret == -1)
	{
		print_error(p_args, "can't cd to ");
		p_eputs(p_args->argv[1]), p_eputchar('\n');
	}
	else
	{
		p__setenv(p_args, "OLDPWD", p_getenv(p_args, "PWD="));
		p__setenv(p_args, "PWD", getcwd(p_buffer, 1024));
	}
	return (0);
}

/**
 * p_help - changes the directory of the child process
 * @p_args: arguments
 * Return: 0
 */
int p_help(info_t *p_args)
{
	char **p_arr;

	p_arr = p_args->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*p_arr);
	return (0);
}
