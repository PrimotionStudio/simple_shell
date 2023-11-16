#include "prime.h"

/**
 * p_interact - Used to check if the shell is interactive
 * @p_info: structure
 * Return: 1
 */
int p_interact(info_t *p_info)
{
	return (isatty(STDIN_FILENO) && p_info->readfd <= 2);
}

/**
 * p_isdelim - checks for a delimeter
 * @p: the char
 * @p_delim: the delim
 * Return: 1, 0
 */
int p_isdelim(char p, char *p_delim)
{
	while (*p_delim)
		if (*p_delim++ == p)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
