#include "prime.h"

/**
 * p_null_free - frees an address and NULLs the pointer (opposite)
 * @pointer: address
 * Return: 1, 0
 */
int p_null_free(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
