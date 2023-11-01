#include "shell.h"

int main(void)
{
	char *cmd;
	size_t cmdsize;

	while (1)
	{
		printf("OurShell $ " );
		getline(&cmd, &cmdsize, stdin);
		cmd[strcspn(cmd, "\n")] = '\0';
		printf("%s \n" , cmd);
	}
	return (0);
}
