#include "prime.h"

void printer(const char *str)
{
        size_t len = 0;
        while (str[len] != '\0')
                len++;
        write(STDOUT_FILENO, str, len);
}
