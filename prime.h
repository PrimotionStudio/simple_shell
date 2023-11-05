#ifndef PRIME_H
#define PRIME_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void p_ctrlc(int p_si);
void printer(const char *str);
size_t _strlen(char *str);

#endif /* PRIME_H */
