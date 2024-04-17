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
		execute(arguments[0], arguments);
}

/**
 * input - function to keep prompting user until exit
 * @command: argument to process
 * @size: size of argument
 */

void input(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
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
	command[strcspn(command, "\n")] = '\0';
}

/**
 * display_prompt - dollar sign to display before each prompt
 */

void display_prompt(void)
{
	printf("$ ");
}

/**
 * main - entry point to program
 * Return: 0 on success
 */

int main(void)
{
	char command[1024];

	while (1)
	{
		display_prompt();
		input(command, sizeof(command));
		if (strcmp(command, "exit") == 0)
			exit(EXIT_SUCCESS);
		parse(command);
	}
	return (0);
}
