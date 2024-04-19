#include "simpleshell.h"

char *fullpath;

/**
 * _getenv - get environment variable
 * @name: name of environment variable
 * Return: pointer to environment variable
 */

char *_getenv(const char *name) {
    extern char **environ;
    char **env, *separator;

    for (env = environ; *env != NULL; env++) {
        separator = strchr(*env, '=');
        if (separator != NULL) {
            if (strncmp(*env, name, separator - *env) == 0) {
                return separator + 1;
            }
        }
    }
    return NULL;
}

/**
 * pathfinder - finds the correct path for given alias
 * @command: given input to check for path
 * Return: pointer to the string array or NULL if failed
 */

char **pathfinder(char *cmd, char **command, char **envp)
{
    char *current_path, *temp_path;
    char *path_tok;
    size_t arglen = strlen(cmd);

    fullpath = NULL;
    (void) envp;
    if (strchr(cmd, '/') != NULL && access(cmd, F_OK) == 0)
    {
        command[0] = cmd;
        return (command);
    }
    path_tok = NULL;
    current_path = _getenv("PATH");
    temp_path = strdup(current_path);
    path_tok = strtok(temp_path, ":");
    while (path_tok)
    {
        fullpath = malloc(arglen + strlen(path_tok) + 2);
        sprintf(fullpath, "%s/%s", path_tok, cmd);
        if (access(fullpath, F_OK) == 0)
        {
            command[0] = fullpath;
            free(temp_path);
            return (command);
        }
        path_tok = strtok(NULL, ":");
        free(fullpath);
    }
    free(temp_path);
    return (NULL);
}

/**
 * execute - function to execute commands
 * @command: input froom user
 * Return: -1 if failed and 0 if success
 */

int execute(char *const command[], char **envp)
{
	pid_t id = fork();
	int status, i;
	char **temp = pathfinder(command[0], (char **) command, envp);

	if (temp != NULL)
	{
		if (id < 0)
		{
			perror("fork failed");
			return (-1);
		}
		else if (id == 0)
		{
			execve(command[0], command, envp);
			perror("command does not exist");
			for (i = 0; command[i] != NULL; i++)
    				free(command[i]);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(fullpath);
	}
	return (0);
}

