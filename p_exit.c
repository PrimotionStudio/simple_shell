#include "prime.h"

/**
 * p_exit - Handles the built-in 'exit' command
 * Description: Exits the shell.
 */
void p_exit(void)
{
	printer("Exiting shell\n");
	exit(EXIT_SUCCESS);
}
