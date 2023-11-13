#include "prime.h"

char *_strdup(const char *source)
{
	int length = 0, i = 0;
	char *duplicate = NULL;
	while (source[length] != '\0')
		length++;

	duplicate = (char *)malloc((length + 1) * sizeof(char));

	if (duplicate != NULL)
	{
		for (i = 0; i < length; i++)
			duplicate[i] = source[i];
		duplicate[length] = '\0';
	}

	return (duplicate);
}
