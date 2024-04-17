#include "simpleshell.h"

/**
 * parse - tokenizes
 * @command: command from the user
 */

void parse(char command[])
{
	char *arguments[10];
	char *token = strtok(command, " ");
	int arg_count = 0;

	while (token != NULL && arg_count < 10)
	{
		arguments[arg_count++] = token;
		token = strtok(NULL, " ");
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

	if ((int)read_bytes == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	if ((*command)[read_bytes - 1] == '\n')
	{
		(*command)[read_bytes - 1] = '\0';
	}
}

/**
 * display_prompt - dollar sign to display before each prompt
 */

void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", strlen("$ "));
}

/**
 * main - entry point to program
 * Return: 0 on success
 */

int main(void) {
    char *command = NULL;
    size_t size = 0;
    while (1) {
        printf("$ ");
        input(&command, &size);
        if (strcmp(command, "exit") == 0) {
            free(command);
            exit(EXIT_SUCCESS);
        }
        parse(command);
    }
    free(command);
    return 0;
}
