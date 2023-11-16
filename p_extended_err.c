#include "prime.h"

/**
 * p_atoi_error - converts a str to int gracefully
 * @p_str: the str
 * Return: 0, -1
 */
int p_atoi_error(char *p_str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*p_str == '+')
		p_str++;
	for (i = 0;  p_str[i] != '\0'; i++)
	{
		if (p_str[i] >= '0' && p_str[i] <= '9')
		{
			result *= 10;
			result += (p_str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	p_eputs(info->fname);
	p_eputs(": ");
	print_int(info->line_count, STDERR_FILENO);
	p_eputs(": ");
	p_eputs(info->argv[0]);
	p_eputs(": ");
	p_eputs(estr);
}

/**
 * print_int - To print an interger
 * @p_int: the int
 * @p_filed: the filedescriptor
 * Return: no of chars
 */
int print_int(int p_int, int p_filed)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (p_filed == STDERR_FILENO)
		__putchar = p_eputchar;
	if (p_int < 0)
	{
		_abs_ = -p_int;
		__putchar('-');
		count++;
	}
	else
		_abs_ = p_int;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * p_iota - replacement for iota
 * @p_int: integer
 * @p_base: base
 * @p_flag: flags
 * Return: string
 */
char *p_iota(long int p_int, int p_base, int p_flag)
{
	static char *p_array;
	static char p_buf[50];
	char p_sign = 0;
	char *pointer;
	unsigned long i = p_int;

	if (!(p_flag & CONVERT_UNSIGNED) && p_int < 0)
	{
		i = -p_int;
		p_sign = '-';
	}
	p_array = p_flag & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pointer = &p_buf[49];
	*pointer = '\0';

	do	{
		*--pointer = p_array[i % p_base];
		i /= p_base;
	} while (i != 0);

	if (p_sign)
		*--pointer = p_sign;
	return (pointer);
}

/**
 * p_comment - Changes a comment to a null terminator
 * @p_str: the string
 * Return: 0;
 */
void p_comment(char *p_str)
{
	int i;

	for (i = 0; p_str[i] != '\0'; i++)
		if (p_str[i] == '#' && (!i || p_str[i - 1] == ' '))
		{
			p_str[i] = '\0';
			break;
		}
}
