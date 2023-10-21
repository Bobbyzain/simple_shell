#include "main.h"

/**
 * info_copy - copies info to be created
 * a new env or alias
 * @name: name (env or alias)
 * @val: val (env or alias)
 *
 * Return: new env or alias.
 */
char *info_copy(char *name, char *val)
{
	char *new;
	int length_name, length_val, length;

	length_name = _strlen(name);
	length_val = _strlen(val);
	length = length_name + length_val + 2;
	new = malloc(sizeof(char) * (length));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, val);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_environment - sets an environment variable
 *
 * @name: name of the environment variable
 * @val: val of the environment variable
 * @shell_d: data structure (environ)
 * Return: no return
 */
void set_environment(char *name, char *val, shell_data *shell_d)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; shell_d->_environ[i]; i++)
	{
		var_env = _strdup(shell_d->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(shell_d->_environ[i]);
			shell_d->_environ[i] = info_copy(name_env, val);
			free(var_env);
			return;
		}
		free(var_env);
	}

	shell_d->_environ = _realocdp(shell_d->_environ, i, sizeof(char *) * (i + 2));
	shell_d->_environ[i] = info_copy(name, val);
	shell_d->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @shell_d: data relevant (env name and env val)
 *
 * Return: 1 on success.
 */
int _setenv(shell_data *shell_d)
{

	if (shell_d->args[1] == NULL || shell_d->args[2] == NULL)
	{
		obt_error(shell_d, -1);
		return (1);
	}

	set_environment(shell_d->args[1], shell_d->args[2], shell_d);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @shell_d: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shell_data *shell_d)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (shell_d->args[1] == NULL)
	{
		obt_error(shell_d, -1);
		return (1);
	}
	k = -1;
	for (i = 0; shell_d->_environ[i]; i++)
	{
		var_env = _strdup(shell_d->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, shell_d->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		obt_error(shell_d, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; shell_d->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = shell_d->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(shell_d->_environ[k]);
	free(shell_d->_environ);
	shell_d->_environ = realloc_environ;
	return (1);
}
