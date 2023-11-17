#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define P_READ_BUFFER_SIZE 1024
#define P_WRITE_BUFFER_SIZE 1024
#define P_BUFFER_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

	/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;	/*  The number field. */
	char *str;	/* a string */
	struct liststr *next;	/* points to the next node */
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int p_shell(info_t *, char **);
int p_get_builtin(info_t *);
void p_get_cmd(info_t *);
void p_fork_cmd(info_t *);
int p_is_cmd(info_t *, char *);
char *p_dup_chars(char *, int, int);
char *p_get_path(info_t *, char *, char *);
int p_loop_shell(char **);
void p_eputs(char *);
int p_eputchar(char);
int p_putfiled(char, int);
int p_putsfiled(char *, int);
int _strlen(char *);
int _strcmp(char *, char *);
char *p_starts(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **_strtok(char *, char *);
char **_strtoken(char *, char);
char *p_set_mem(char *, char, unsigned int);
void p_free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int p_null_free(void **);
int p_interact(info_t *);
int p_isdelim(char, char *);
int _isalpha(int);
int _atoi(char *);
int p_atoi_error(char *);
void print_error(info_t *, char *);
int print_int(int, int);
char *p_iota(long int, int, int);
void p_comment(char *);
int p_exit(info_t *);
int p_cd(info_t *);
int p_help(info_t *);
int p_history(info_t *);
int p_alias(info_t *);
ssize_t p_get_input(info_t *);
int p_getline(info_t *, char **, size_t *);
void p_ctrlc(int);
void p_clear_info(info_t *);
void p_set_info(info_t *, char **);
void p_free_info(info_t *, int);
char *p_getenv(info_t *, const char *);
int p_env(info_t *);
int p_setenv(info_t *);
int p_unsetenv(info_t *);
int p_set_env_list(info_t *);
char **p__getenv(info_t *);
int p__unsetenv(info_t *, char *);
int p__setenv(info_t *, char *, char *);
char *p_get_history(info_t *info);
int p_write_history(info_t *info);
int p_read_history(info_t *info);
int p_build_history(info_t *info, char *buf, int linecount);
int p_reno_history(info_t *info);
list_t *p_add_node(list_t **, const char *, int);
list_t *p_add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int p_delete_node(list_t **, unsigned int);
void p_free_list(list_t **);
size_t p_list_len(const list_t *);
char **p_list_strings(list_t *);
size_t print_list(const list_t *);
list_t *p_startnode(list_t *, char *, char);
ssize_t p_get_node(list_t *, list_t *);
int p_is_chain(info_t *, char *, size_t *);
void p_check_chain(info_t *, char *, size_t *, size_t, size_t);
int p_replace_alias(info_t *);
int p_replace_vars(info_t *);
int p_replace_string(char **, char *);

#endif
