#include "main.h"

/**
 * _which - check if the command exist in one of the directories
 * @command: the command to search for
 * @path: the path to search through
 * Return: return pointer to char
 */

char *_which(char *command, char *path)
{
	char *token, *path_copy, *full_path;
	struct stat st;
	int i = 0;

	if (!command || !path)
		return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	/* Tokenize the PATH variable */
	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		i = stat(full_path, &st);
		if (i == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
