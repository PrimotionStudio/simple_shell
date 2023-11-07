#include "prime.h"

/**
 * printer - Used in place of printf
 * @str: The string to print
 */
void printer(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
		len++;
	write(STDOUT_FILENO, str, len);
}
