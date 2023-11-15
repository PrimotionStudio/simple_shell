#include "prime.h"

/**
 * _strchr - Custom replacement for strchr
 * @str: The string to search
 * @ch: The character to find
 * Return: A pointer to the first occurrence of the character,
 *         or NULL if the character is not found
 */
char *_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}
/**
 * _strcspn - Replacement for strcspn
 * @str: The string
 * @reject: The reject
 * Return: The position
 */
size_t _strcspn(const char *str, const char *reject)
{
	const char *s = str;

	while (*s)
	{
		if (_strchr(reject, *s))
			break;
		s++;
	}
	return (s - str);
}
