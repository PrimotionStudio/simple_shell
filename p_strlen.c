#include "prime.h"

/**
 * _strlen - To get the length of a string
 * @str: The string to check
 * Return: The lenght
 */
size_t _strlen(char *str)
{
	size_t len = 0;

	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}
