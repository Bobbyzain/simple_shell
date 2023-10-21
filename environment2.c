#include "main.h"

/**
 * compare_env_name - compares env variables names
 * with the name passed.
 * @env_name: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_env_name(const char *env_name, const char *name)
{
	int i;

	for (i = 0; env_name[i] != '='; i++)
	{
		if (env_name[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenvironment - get an environment variable
 * @n: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenvironment(const char *n, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = compare_env_name(_environ[i], n);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @shell_d: data relevant.
 * Return: 1 on success.
 */
int _env(shell_data *shell_d)
{
	int i, j;

	for (i = 0; shell_d->_environ[i]; i++)
	{

		for (j = 0; shell_d->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, shell_d->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_d->status = 0;

	return (1);
}

