#include "main.h"

/**
 * _execution_line - finds builtins and commands
 *
 * @shell_d: data relevant (args)
 * Return: 1 on success.
 */
int _execution_line(shell_data *shell_d)
{
	int (*builtin)(shell_data *shell_d);

	if (shell_d->args[0] == NULL)
		return (1);

	builtin = get_built_in(shell_d->args[0]);

	if (builtin != NULL)
		return (builtin(shell_d));

	return (cmd_exec(shell_d));
}

/**
 * exit_shell - to exit the shell
 * @dsh: the relevant data
 * Return: Always int
 */
int exit_shell(shell_data *dsh)
{
	unsigned int uint_status; /* default exit status */
	int is_num, str_length, big_num;

	if (dsh->args[1] != NULL)
	{
		uint_status = _atoi(dsh->args[1]);
		is_num =  _isdigit(dsh->args[1]);
		str_length = _strlen(dsh->args[1]);
		big_num = uint_status > (unsigned int)INT_MAX;
		if (!is_num || str_length > 10 || big_num)
		{
			obt_error(dsh, 2);
			dsh->status = 2;
			return (1);
		}
		dsh->status = (uint_status % 256);
	}
	return (0);
}
/**
 * obt_error - the error called using builtin as guide
 * @shell_d: the structure containing args
 * @err_val: value of error
 * Return: always int
 */
int obt_error(shell_data *shell_d, int err_val)
{
	char *error;

	switch (err_val)
	{
	case -1:
		error = error_environment(shell_d);
		break;
	case 126:
		error = error_path126(shell_d);
		break;
	case 127:
		error = error_not_f(shell_d);
		break;
	case 2:
		if (_strcmp("exit", shell_d->args[0]) == 0)
			error = err_exit_shell(shell_d);
		else if (_strcmp("cd", shell_d->args[0]) == 0)
			error = err_get_cd(shell_d);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	shell_d->status = err_val;
	return (err_val);
}
/**
 * error_environment - the error msg for env in getenv
 * @shell_d: relevant structure
 * Return: Always pointer
 */
char *error_environment(shell_data *shell_d)
{
	int len;
	char *error;
	char *ver_str;
	char *message;

	ver_str = aux_itoa(shell_d->counter);
	message = ": Unable to add/remove from environment\n";
	len = _strlen(shell_d->av[0]) + _strlen(ver_str);
	len += _strlen(shell_d->args[0]) + _strlen(message) + 4;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, shell_d->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_d->args[0]);
	_strcat(error, message);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path126 - error for path and failure denied permission.
 * @shell_d: relevant structure containing args
 * Return: Always pointer
 */
char *error_path126(shell_data *shell_d)
{
	int len;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(shell_d->counter);
	len = _strlen(shell_d->av[0]) + _strlen(ver_str);
	len += _strlen(shell_d->args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shell_d->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_d->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
