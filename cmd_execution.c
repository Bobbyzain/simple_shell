#include "main.h"

/**
 * is_current_dir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *p_path, *token_path, *directory;
	int len_directory, len_cmd, i;
	struct stat st;

	path = _getenvironment("PATH", _environ);
	if (path)
	{
		p_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(p_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_directory = _strlen(token_path);
			directory = malloc(len_directory + len_cmd + 2);
			_strcpy(directory, token_path);
			_strcat(directory, "/");
			_strcat(directory, cmd);
			_strcat(directory, "\0");
			if (stat(directory, &st) == 0)
			{
				free(p_path);
				return (directory);
			}
			free(directory);
			token_path = _strtok(NULL, ":");
		}
		free(p_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @shell_d: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(shell_data *shell_d)
{
	struct stat st;
	int i;
	char *input;

	input = shell_d->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	obt_error(shell_d, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @directory: destination directory
 * @shell_d: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *directory, shell_data *shell_d)
{
	if (directory == NULL)
	{
		obt_error(shell_d, 127);
		return (1);
	}

	if (_strcmp(shell_d->args[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			obt_error(shell_d, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(shell_d->args[0], X_OK) == -1)
		{
			obt_error(shell_d, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @shell_d: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(shell_data *shell_d)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *directory;
	(void) wpd;

	exec = is_executable(shell_d);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		directory = _which(shell_d->args[0], shell_d->_environ);
		if (check_error_cmd(directory, shell_d) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			directory = _which(shell_d->args[0], shell_d->_environ);
		else
			directory = shell_d->args[0];
		execve(directory + exec, shell_d->args, shell_d->_environ);
	}
	else if (pd < 0)
	{
		perror(shell_d->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell_d->status = state / 256;
	return (1);
}
