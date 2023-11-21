#include "prime.h"

/**
  * _strcmp - Replace ment for strcmp
  * @str1: arg
  * @str2: arg
  * Return: The difference
  */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
