#include "shell.h"

int main(void)
{
    char cmd[100];
    size_t cmdsize;
    while (1)
    {
        printf("OurShell $ " );
        getline(&cmd, &cmdsize, stdin);
        printf("%s \n" , cmd);
    }
return (0);
}
