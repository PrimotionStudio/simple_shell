#include "shell.h"

int main(void)
{
	char *cmd;
	size_t cmdsize;

	while (1)
	{
		printf("OurShell $ " );
		if (getline(&cmd, &cmdsize, stdin) == -1)
        {
           printf("\n");
            return (0);
        }
		cmd[strcspn(cmd, "\n")] = '\0';
		printf("%s \n" , cmd);
	}
	return (0);
}
