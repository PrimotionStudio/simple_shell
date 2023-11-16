#include "prime.h"

/**
 * p_set_mem - enters in memory with a specifc byte
 * @p_value: the memory
 * @p_bytes: the byts
 * @p_no: the amount
 * Return: memory used
 */
char *p_set_mem(char *p_value, char p_bytes, unsigned int p_no)
{
	unsigned int i;

	for (i = 0; i < p_no; i++)
		p_value[i] = p_bytes;
	return (p_value);
}

/**
 * p_free - frees an array of str
 * @p_arr: array of strings
 */
void p_free(char **p_arr)
{
	char **a = p_arr;

	if (!p_arr)
		return;
	while (*p_arr)
		free(*p_arr++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
