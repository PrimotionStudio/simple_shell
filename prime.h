#ifndef SHELL_PRIME_H
#define SHELL_PRIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void printer(const char *str);
void p_ctrlc(int p_si);
char **parse_cmd(char *p_line);
void p_exec(char **p_args);
void p_env(void);
void p_exit(void);
void p_line_error(int p_read_bytes, char *p_line);
char *_strtok(char *str, char *delim);
ssize_t _getline(char **lineptr, size_t *n, FILE *fd);
size_t _strcspn(const char *str, const char *reject);
int _strcmp(const char *str1, const char *str2);
char *_strdup(const char *source);

extern char **environ;

#define BUFFER_SIZE 128

#endif /* SHELL_PRIME_H */
