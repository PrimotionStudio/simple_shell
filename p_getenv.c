#include "prime.h"

/**
 * p__getenv - returns a string of the env
 * @p_args: arguments
 * Return: 0
 */
char **p__getenv(info_t *p_args)
{
	if (!p_args->environ || p_args->env_changed)
	{
		p_args->environ = p_list_strings(p_args->env);
		p_args->env_changed = 0;
	}
	return (p_args->environ);
}

/**
 * p__unsetenv - Unsets env
 * @p_args: arguments
 * @p_en: the env
 * Return: 1, 0
 */
int p__unsetenv(info_t *p_args, char *p_en)
{
	list_t *new = p_args->env;
	size_t i = 0;
	char *p;

	if (!new || !p_en)
		return (0);

	while (new)
	{
		p = p_starts(new->str, p_en);
		if (p && *p == '=')
		{
			p_args->env_changed = p_delete_node(&(p_args->env), i);
			i = 0;
			new = p_args->env;
			continue;
		}
		new = new->next;
		i++;
	}
	return (p_args->env_changed);
}

/**
 * p__setenv - Initialize an env
 * @p_args: arguments
 * @en: the env name
 * @val: the env value
 * Return: 0
 */
int p__setenv(info_t *p_args, char *en, char *val)
{
	char *buffer = NULL;
	list_t *new;
	char *p;

	if (!en || !val)
		return (0);

	buffer = malloc(_strlen(en) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, en);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	new = p_args->env;
	while (new)
	{
		p = p_starts(new->str, en);
		if (p && *p == '=')
		{
			free(new->str);
			new->str = buffer;
			p_args->env_changed = 1;
			return (0);
		}
		new = new->next;
	}
	p_add_node_end(&(p_args->env), buffer, 0);
	free(buffer);
	p_args->env_changed = 1;
	return (0);
}
