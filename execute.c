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

char **pathfinder(char *cmd, char **command)
{
    char *current_path, *temp_path;
    char *path_tok;
    size_t arglen = strlen(cmd);

    fullpath = NULL;
    if (strchr(cmd, '/') != NULL && access(cmd, F_OK) == 0)
    {
        command[0] = cmd;
        return (command);
    }
    path_tok = NULL;
    current_path = _getenv("PATH");
  /*  if (current_path == NULL || *current_path == '\0')
    {
	    perror("./hsh: 1: ls: not found");
	    exit(EXIT_FAILURE);
    }*/
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
	pid_t id;
	int status, i;
	char **temp = pathfinder(command[0], (char **) command);

	if (temp != NULL)
	{
		id = fork();
		if (id < 0)
		{
			perror("fork failed");
			return (-1);
		}
		else if (id == 0)
		{
			if (_getenv("PATH") == NULL && access(command[0], F_OK) != 0)
            		{
                		fprintf(stderr, "./hsh: 1: %s: not found\n", command[0]);
                		exit(EXIT_FAILURE);
            		}
			execve(temp[0], command, envp);
			for (i = 0; command[i] != NULL; i++)
    				free(command[i]);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(fullpath);
	} else
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command[0]);
		free(*command);
		exit(127);
	}
	return (0);
}

