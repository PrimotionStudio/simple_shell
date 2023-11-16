#include "prime.h"

/**
 * **_strtok - replacement for strtok
 * @p_str: the string
 * @p_delim: the delimeter
 * Return: array of tokens or NULL
 */
char **_strtok(char *p_str, char *p_delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (p_str == NULL || p_str[0] == 0)
		return (NULL);
	if (!p_delim)
		p_delim = " ";
	for (i = 0; p_str[i] != '\0'; i++)
		if (!p_isdelim(p_str[i], p_delim) && (p_isdelim(p_str[i + 1],
			p_delim) || !p_str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (p_isdelim(p_str[i], p_delim))
			i++;
		k = 0;
		while (!p_isdelim(p_str[i + k], p_delim) && p_str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = p_str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **_strtoken - tokenizes a string
 * @p_str: the string
 * @p_delim: the delimeter
 * Return: array of tokens or null
 */
char **_strtoken(char *p_str, char p_delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (p_str == NULL || p_str[0] == 0)
		return (NULL);
	for (i = 0; p_str[i] != '\0'; i++)
		if ((p_str[i] != p_delim && p_str[i + 1] == p_delim) ||
				    (p_str[i] != p_delim && !p_str[i + 1]) || p_str[i + 1] == p_delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (p_str[i] == p_delim && p_str[i] != p_delim)
			i++;
		k = 0;
		while (p_str[i + k] != p_delim && p_str[i + k] && p_str[i + k] != p_delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = p_str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
