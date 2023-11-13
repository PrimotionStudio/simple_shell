#include "prime.h"

size_t _strcspn(const char *str, const char *reject)
{
	const char *s = str;
	while (*s)
	{
		if (strchr(reject, *s))
			break;
		s++;
	}
	return (s - str);
}
