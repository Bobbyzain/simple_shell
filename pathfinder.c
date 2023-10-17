#include "main.h"

/**
 * get_loc - function to get the path location of a command
 * @command: the command whose location is sought
 * Return: location
 */

char *get_loc(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;
	int cmd_len = _strlen(command), dir_len, i;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		path_token = _strtok(path_copy, ":");
		i = 0;
		while (path_token != NULL)
		{
			if (in_currentdir(path, &i))
				if (stat(command, &buffer) == 0)
					return (command);
			dir_len = _strlen(path_token); /*To get the len of dir*/
			file_path = malloc(cmd_len + dir_len + 2);
			/* Building the new path for the command */
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			/*check to see if filepath exist, 0 for success */
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			free(file_path); /* free up mem for other use*/
			path_token = _strtok(NULL, ":");
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
			return (command);
		return (NULL);
	}
	/*if (command[0] == '/')*/
		/*if (stat(command, &buffer) == 0)*/
			/*return (command);*/
	return (NULL);
}
/**
 * in_currentdir -  to check if file is in current directory
 * @path: pointer to the path
 * @j: the index of the pointer
 * Return: Always int
 */
int in_currentdir(char *path, int *j)
{
	if (path[*j] == ':')
		return (1);

	while (path[*j] != ':' && path[*j])
		*j += 1;
	return (0);
}
