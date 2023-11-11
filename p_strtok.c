#include "prime.h"

char *_strtok(char *str, char *delim)
{
	static char *remaining = NULL;
	char *newstr = NULL;
	int j = 0, m = 0, i = 0, n = 0, o = 0;

	if (!str)
	{
		str = remaining;
	}
	if (*str == '\0')
		return (NULL);
	while (str[i] != '\0')
		i++;
	while (j < i && str[j] != *delim)
		j++;
	newstr = (char *)malloc(j + 1);
	if (!newstr)
		return (NULL);
	while (m < j && str[m] != *delim)
	{
		newstr[m] = str[m];
		m++;
	}
	newstr[m] = '\0';
	n = i - j;
	remaining = (char *)malloc(n + 1);
	if (!remaining)
	{
		free(newstr);
		return (NULL);
	}
	while (o < n)
	{
		remaining[o] = str[j + 1];
		j++;
		o++;
	}
	remaining[o] = '\0';
	return(newstr);
}
