#include "prime.h"

/**
 * p_list_len - gets d length of a list
 * @p: head node
 * Return: lnghtof list
 */
size_t p_list_len(const list_t *p)
{
	size_t i = 0;

	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

/**
 * p_list_strings - Convrt a list to string
 * @p_head: head
 * Return: strings arr
 */
char **p_list_strings(list_t *p_head)
{
	list_t *cur = p_head;
	size_t i = p_list_len(p_head), j;
	char **strs;
	char *str;

	if (!p_head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; cur; cur = cur->next, i++)
	{
		str = malloc(_strlen(cur->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, cur->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @p: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *p)
{
	size_t i = 0;

	while (p)
	{
		_puts(p_iota(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		i++;
	}
	return (i);
}

/**
 * p_startnode - Gets a node with a prefix
 * @p_node: head
 * @pre: prefix
 * @c: character after prefix
 * Return: node or null
 */
list_t *p_startnode(list_t *p_node, char *pre, char c)
{
	char *p = NULL;

	while (p_node)
	{
		p = p_starts(p_node->str, pre);
		if (p && ((c == -1) || (*p == c)))
			return (p_node);
		p_node = p_node->next;
	}
	return (NULL);
}

/**
 * p_get_node - gets a node
 * @p_head: head
 * @new: new
 * Return: node or -1
 */
ssize_t p_get_node(list_t *p_head, list_t *new)
{
	size_t i = 0;

	while (p_head)
	{
		if (p_head == new)
			return (i);
		p_head = p_head->next;
		i++;
	}
	return (-1);
}
