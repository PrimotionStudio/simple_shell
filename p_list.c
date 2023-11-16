#include "prime.h"

/**
 * p_add_node - append a node to the head of the list
 * @p_head: dead
 * @p_str: str
 * @p_val: value
 * Return: new size of list
 */
list_t *p_add_node(list_t **p_head, const char *p_str, int p_val)
{
	list_t *p_new_head;

	if (!p_head)
		return (NULL);
	p_new_head = malloc(sizeof(list_t));
	if (!p_new_head)
		return (NULL);
	p_set_mem((void *)p_new_head, 0, sizeof(list_t));
	p_new_head->num = p_val;
	if (p_str)
	{
		p_new_head->str = _strdup(p_str);
		if (!p_new_head->str)
		{
			free(p_new_head);
			return (NULL);
		}
	}
	p_new_head->next = *p_head;
	*p_head = p_new_head;
	return (p_new_head);
}

/**
 * p_add_node_end - append a node to the end of the list
 * @p_head: the head of the list
 * @p_str: string
 * @p_val: value or index
 * Return: new size of list
 */
list_t *p_add_node_end(list_t **p_head, const char *p_str, int p_val)
{
	list_t *p_new_node, *new;

	if (!p_head)
		return (NULL);

	new = *p_head;
	p_new_node = malloc(sizeof(list_t));
	if (!p_new_node)
		return (NULL);
	p_set_mem((void *)p_new_node, 0, sizeof(list_t));
	p_new_node->num = p_val;
	if (p_str)
	{
		p_new_node->str = _strdup(p_str);
		if (!p_new_node->str)
		{
			free(p_new_node);
			return (NULL);
		}
	}
	if (new)
	{
		while (new->next)
			new = new->next;
		new->next = p_new_node;
	}
	else
		*p_head = p_new_node;
	return (p_new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * p_delete_node - deletes a specific node
 * @p_head: head of theh node
 * @p: index
 * Return: 1, 0
 */
int p_delete_node(list_t **p_head, unsigned int p)
{
	list_t *cur, *prev_node;
	unsigned int i = 0;

	if (!p_head || !*p_head)
		return (0);

	if (!p)
	{
		cur = *p_head;
		*p_head = (*p_head)->next;
		free(cur->str);
		free(cur);
		return (1);
	}
	cur = *p_head;
	while (cur)
	{
		if (i == p)
		{
			prev_node->next = cur->next;
			free(cur->str);
			free(cur);
			return (1);
		}
		i++;
		prev_node = cur;
		cur = cur->next;
	}
	return (0);
}

/**
 * p_free_list - frees all nodes
 * @p_headptr: address of pointer to head node
 */
void p_free_list(list_t **p_headptr)
{
	list_t *cur, *next_node, *p_head;

	if (!p_headptr || !*p_headptr)
		return;
	p_head = *p_headptr;
	cur = p_head;
	while (cur)
	{
		next_node = cur->next;
		free(cur->str);
		free(cur);
		cur = next_node;
	}
	*p_headptr = NULL;
}
