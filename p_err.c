#include "prime.h"

/**
 * p_eputs - prints input
 * @p_str: the string
 */
void p_eputs(char *p_str)
{
	int i = 0;

	if (!p_str)
		return;
	while (p_str[i] != '\0')
	{
		p_eputchar(p_str[i]);
		i++;
	}
}

/**
 * p_eputchar - writes to stderr
 * @c: The character
 * Return: 1, -1
 */
int p_eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * p_putfiled - writes to file
 * @p: The character to print
 * @p_fd: The filedescriptor to write to
 * Return: 1, -1
 */
int p_putfiled(char p, int p_fd)
{
	static int i;
	static char p_buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(p_fd, p_buf, i);
		i = 0;
	}
	if (p != BUF_FLUSH)
		p_buf[i++] = p;
	return (1);
}

/**
 * p_putsfiled - prints whole string
 * @p_str: the string
 * @p_fd: the file
 * Return: no of chars
 */
int p_putsfiled(char *p_str, int p_fd)
{
	int i = 0;

	if (!p_str)
		return (0);
	while (*p_str)
	{
		i += p_putfiled(*p_str++, p_fd);
	}
	return (i);
}
