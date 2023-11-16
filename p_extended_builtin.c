#include "prime.h"

/**
 * p_history - displays the history of commands
 * @p_args: arguments
 *  Return: 0
 */
int p_history(info_t *p_args)
{
	print_list(p_args->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = p_delete_node(&(info->alias),
			p_get_node(info->alias, p_startnode(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (p_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * p_alias - replacement for alias
 * @p_args: arguments
 *  Return: 0
 */
int p_alias(info_t *p_args)
{
	int i = 0;
	char *p = NULL;
	list_t *new_alias = NULL;

	if (p_args->argc == 1)
	{
		new_alias = p_args->alias;
		while (new_alias)
		{
			print_alias(new_alias);
			new_alias = new_alias->next;
		}
		return (0);
	}
	for (i = 1; p_args->argv[i]; i++)
	{
		p = _strchr(p_args->argv[i], '=');
		if (p)
			set_alias(p_args, p_args->argv[i]);
		else
			print_alias(p_startnode(p_args->alias, p_args->argv[i], '='));
	}

	return (0);
}
