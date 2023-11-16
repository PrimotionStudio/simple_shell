#include "prime.h"

/**
 * p_env - prints env
 * @p_args: arguments
 * Return: 0
 */
int p_env(info_t *p_args)
{
	print_list_str(p_args->env);
	return (0);
}

/**
 * p_getenv - gets an env value
 * @p_args: arguments
 * @en: EN name
 * Return: en value
 */
char *p_getenv(info_t *p_args, const char *en)
{
	list_t *new = p_args->env;
	char *p;

	while (new)
	{
		p = p_starts(new->str, en);
		if (p && *p)
			return (p);
		new = new->next;
	}
	return (NULL);
}

/**
 * p_setenv - Sets and env value
 * @p_args: arguments
 *  Return: 0
 */
int p_setenv(info_t *p_args)
{
	if (p_args->argc != 3)
	{
		p_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (p__setenv(p_args, p_args->argv[1], p_args->argv[2]))
		return (0);
	return (1);
}

/**
 * p_unsetenv - Unsets an env
 * @p_args: arguments
 * Return: 0
 */
int p_unsetenv(info_t *p_args)
{
	int p;

	if (p_args->argc == 1)
	{
		p_eputs("Too few arguements.\n");
		return (1);
	}
	for (p = 1; p <= p_args->argc; p++)
		p__unsetenv(p_args, p_args->argv[p]);

	return (0);
}

/**
 * p_set_env_list - sets env linked list
 * @p_args: arguments
 * Return: 0
 */
int p_set_env_list(info_t *p_args)
{
	list_t *new = NULL;
	size_t p;

	for (p = 0; environ[p]; p++)
		p_add_node_end(&new, environ[p], 0);
	p_args->env = new;
	return (0);
}
