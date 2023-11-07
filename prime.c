#include "prime.h"
extern char **environ;

/**
 * p_ctrlc - Handles the SIGINT signal (Ctrl+C) to prevent termination
 * @p_si: Signal number (unused)
 *
 * Description: Prints a new line and prompts the user for input.
 */
void p_ctrlc(int p_si)
{
    (void)p_si;
    printf("\n$ ");
    fflush(stdout);
}

/**
 * parse_command - Parses the input command line into individual arguments
 * @line: The input command line string
 *
 * Return: An array of strings containing individual arguments.
 *         NULL on failure.
 *
 * Description: Tokenizes the input line using space as the delimiter.
 *              Allocates memory for arguments and copies tokens.
 */
char **parse_command(char *line)
{
     char **args = NULL;
    char *token = NULL;
    size_t p = 0;

    args = malloc(sizeof(char *) * 64);
    if (args == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token != NULL) {
        args[p] = strdup(token);
        if (args[p] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " ");
        p++;
    }
    args[p] = NULL;

    return args;
}

/**
 * execute_command - Executes the given command with arguments
 * @args: An array of strings containing the command and its arguments
 *
 * Description: Forks a child process to execute the specified command.
 *              Handles command execution and error messages.
 */
void execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
    }
}

/**
 * built_in_exit - Handles the built-in 'exit' command
 *
 * Description: Exits the shell.
 */
void built_in_exit(void)
{
    printf("Exiting shell\n");
    exit(EXIT_SUCCESS);
}

/**
 * built_in_env - Handles the built-in 'env' command
 *
 * Description: Prints the current environment variables.
 */
void built_in_env(void)
{
   char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

/**
 * main - Entry point of the shell program
 * Return: Always returns 0
 *
 * Description: Displays a prompt, reads user input, parses and executes commands.
 */
int main(void)
{
    char *line = NULL;
    size_t linesize = 0;
    ssize_t read_bytes;
    char **args;

    signal(SIGINT, p_ctrlc);

    while (1)
    {
        printf("$ ");
        read_bytes = getline(&line, &linesize, stdin);

        if (read_bytes == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                free(line);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        line[strcspn(line, "\n")] = '\0';

        if (line[0] != '\0')
        {
            args = parse_command(line);
            if (args)
            {
                if (strcmp(args[0], "exit") == 0) {
                    built_in_exit();
                } else if (strcmp(args[0], "env") == 0) {
                    built_in_env();
                } else {
                    execute_command(args);
                }
                free(args);
            }
        }

        free(line);
        line = NULL;
        linesize = 0;
    }

    return 0;
}

