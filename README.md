# ALX Simple Shell Group Project

**Authors:**
- Martins Obomate Okanlawon - [GitHub Profile](https://github.com/PrimotionStudio)
- Prosper Abudu - [GitHub Profile](https://github.com/proabudu)

## Description

This Simple Shell is a minimalist Unix-like shell created to replicate the functionality of the existing `/bin/sh`. It provides a basic command-line interface that allows users to interact with the system. This shell is designed to handle simple commands with limited features. Below are the core functionalities and features of this custom shell:

### Features

1. **Display a Prompt:** The shell displays a prompt and waits for the user to enter a command. Each command line ends with a new line. The prompt is displayed again after each command execution.

2. **Simple Command Lines:** The command lines supported by this shell are simple and do not include advanced features such as semicolons, pipes, redirections, or complex scripting.

3. **Single Word Commands:** This shell is designed to work with single-word commands. It does not support passing arguments to programs.

4. **Error Handling:** If an executable command cannot be found, the shell prints an error message and displays the prompt again. It handles various errors gracefully.

5. **End of File Condition:** The shell handles the "end of file" condition, typically triggered by Ctrl+D, ensuring the application behaves appropriately.

6. **Command Lines with Arguments:** This shell can process command lines with arguments. While it primarily supports single-word commands, arguments can be included.

7. **PATH Handling:** The shell can locate executable commands in the system's PATH. It searches for the specified command in the directories listed in the PATH environment variable.

8. **Exit Built-in Command:** The shell implements the `exit` built-in command, which allows the user to exit the shell. The usage is as follows:

   ```
   Usage: exit
   ```

   No arguments are required for the `exit` command.

9. **Env Built-in Command:** The shell also includes the `env` built-in command, which prints the current environment. This command provides a glimpse of the shell's environment variables.

   You are not allowed to use `strtok` to implement this feature.

10. **Fork Handling:** The shell ensures that the `fork` system call is not invoked if the specified command does not exist. This prevents unnecessary forking and ensures efficient execution.

### Examples

Here are a few examples of how to use the simple shell:

1. Running a simple command:

   ```
   $ ls
   (output of 'ls' command)
   $

2. Using the `exit` built-in command to exit the shell:

   ```
   $ exit
   Goodbye!
   $

3. Displaying the current environment using the `env` built-in command:

   ```
   $ env
   (list of environment variables)
   $

## How to Use

1. Clone the repository:

   ```bash
   git clone https://github.com/PrimotionStudio/simple_shell.git
   ```

2. Compile the source code:

   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

3. Run the shell:

   ```bash
   ./hsh
   ```

4. Start entering commands as described in the features section.

## Dependencies

This simple shell has no external dependencies. It is designed to work on Unix-like systems.

## Limitations

- This shell is intended for educational purposes and may not cover the full functionality of a typical Unix shell.
- It does not support advanced features such as pipes, semicolons, or complex scripting.

## License

This simple shell is open-source and released under the MIT License. You are free to use, modify, and distribute it according to the terms of the license.

## Contribution

If you would like to contribute to the development of this simple shell, please create a pull request on the GitHub repository. We welcome contributions and improvements.

Feel free to contact the authors for any questions or issues related to the simple shell.

## Contact Information

- Martins Obomate Okanlawon: [oyedelenewton@gmail.com](mailto:oyedelenewton@gmail.com)
- Prosper Abudu: [abuduprosperyao@gmail.com](abuduprosperyao@gmail.com)
