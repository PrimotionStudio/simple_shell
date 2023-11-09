#include "prime.h"

/**
 * p_ctrlc - Handles the SIGINT signal (Ctrl+C) to prevent termination
 * @p_si: Signal number (unused)
 *
 * Description: Prints a new line and prompts the user for input.
 */
void p_ctrlc(int p_si)
{
	(void)p_si;
	printer("\n$ ");
	fflush(stdout);
}
