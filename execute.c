#include "simpleshell.h"

/**
 * execute - function to execute commands
 * @cmd: argument to execute
 * @command: input froom user
 * Return: -1 if failed and 0 if success
 */

int execute(char *cmd, char *const command[])
{
	pid_t id = fork();
	char full_path[256];
	int status;

	if (id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (id == 0)
	{
		snprintf(full_path, sizeof(full_path), "/usr/bin/%s", cmd);
		execve(full_path, command, NULL);
		perror("execv failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
