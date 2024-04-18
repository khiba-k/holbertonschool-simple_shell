#include "simpleshell.h"

/**
 * execute - function to execute commands
 * @command: input froom user
 * Return: -1 if failed and 0 if success
 */

int execute(char *const command[])
{
	pid_t id = fork();
	int status, i;

	if (id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (id == 0)
	{
		execvp(command[0], command);
		perror("command does not exist");
		for (i = 0; command[i] != NULL; i++) {
    			free(command[i]);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
	return (0);
}

