#include "prime.h"

/**
 * main - The prime shell
 * @ac: no of aruments
 * @av: array of arguments
 * Return: 0, 1
 */
int main(int ac, char **av)
{
	info_t p_args[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				p_eputs(av[0]);
				p_eputs(": 0: Can't open ");
				p_eputs(av[1]);
				p_eputchar('\n');
				p_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		p_args->readfd = fd;
	}
	p_set_env_list(p_args);
	p_read_history(p_args);
	p_shell(p_args, av);
	return (EXIT_SUCCESS);
}
