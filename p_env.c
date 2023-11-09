#include "prime.h"

/**
 * p_env - Handles the built-in 'env' command
 * Description: Prints the current environment variables.
 */
void p_env(void)
{
	char **penv = environ;

	while (*penv != NULL)
	{
		printer(*penv);
		penv++;
	}
}
