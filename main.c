#include "simpleshell.h"

/**
 * parse - tokenizes
 * @command: command from the user
 */

void parse(char command[])
{
	char *arguments[11];
	char *token = strtok(command, " ");
	int arg_count = 0;

	while (token != NULL && arg_count < 10)
	{
		arguments[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	if (arg_count > 11)
        {
                perror("Error: Too many arguments");
                return;
        }
	arguments[arg_count] = NULL;
	if (arg_count > 0)
		execute(arguments);
}

/**
 * input - function to keep prompting user until exit
 * @command: argument to process
 * @size: size of argument
 */

void input(char **command, size_t *size)
{
	size_t read_bytes;

	read_bytes = getline(command, size, stdin);
	if ((int) read_bytes == EOF)
	{
		if (isatty(STDIN_FILENO) != 0)
			printf("\n");
		free(command);
		exit(EXIT_SUCCESS);
	}
	if ((*command)[read_bytes - 1] == '\n')
		(*command)[read_bytes - 1] = '\0';
}

/**
 * main - entry point to program
 * Return: 0 on success
 */

int main(int argc, char *argv[]) {
    char *command = NULL;
    size_t size;

    (void) argv;
    if (argc > 1)
    {
	    printf("./shell: command does not exist");
	    exit(EXIT_FAILURE);
    }
    while (1) {
	size = 0;
	if (isatty(STDIN_FILENO))
	       printf("($) ");	
        input(&command, &size);
        if (strcmp(command, "exit") == 0) {
            free(command);
            exit(EXIT_SUCCESS);
        }
        parse(command);
	free(command);
    }
    return 0;
}

