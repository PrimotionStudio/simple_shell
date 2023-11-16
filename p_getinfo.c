#include "prime.h"

/**
 * p_clear_info - NULLs the info_t
 * @p_args: structure
 */
void p_clear_info(info_t *p_args)
{
	p_args->arg = NULL;
	p_args->argv = NULL;
	p_args->path = NULL;
	p_args->argc = 0;
}

/**
 * p_set_info - initializes info_t
 * @p_info: structure
 * @av: argument
 */
void p_set_info(info_t *p_info, char **av)
{
	int i = 0;

	p_info->fname = av[0];
	if (p_info->arg)
	{
		p_info->argv = _strtok(p_info->arg, " \t");
		if (!p_info->argv)
		{
			p_info->argv = malloc(sizeof(char *) * 2);
			if (p_info->argv)
			{
				p_info->argv[0] = _strdup(p_info->arg);
				p_info->argv[1] = NULL;
			}
		}
		for (i = 0; p_info->argv && p_info->argv[i]; i++)
			;
		p_info->argc = i;

		replace_alias(p_info);
		replace_vars(p_info);
	}
}

/**
 * p_free_info - frees info_t
 * @p_args: structure
 * @p_all: to free all
 */
void p_free_info(info_t *p_args, int p_all)
{
	p_free(p_args->argv);
	p_args->argv = NULL;
	p_args->path = NULL;
	if (p_all)
	{
		if (!p_args->cmd_buf)
			free(p_args->arg);
		if (p_args->env)
			p_free_list(&(p_args->env));
		if (p_args->history)
			p_free_list(&(p_args->history));
		if (p_args->alias)
			p_free_list(&(p_args->alias));
		p_free(p_args->environ);
			p_args->environ = NULL;
		p_null_free((void **)p_args->cmd_buf);
		if (p_args->readfd > 2)
			close(p_args->readfd);
		_putchar(BUF_FLUSH);
	}
}
