#include "main.h"

/**
 * error_not_f - error msg when a command is not found
 * @shell_d: the relevant data structure containing parameters
 * Return: Always a pointer
 */
char *error_not_f(shell_data *shell_d)
{
	int len;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(shell_d->counter);
	len = _strlen(shell_d->av[0]) + _strlen(ver_str);
	len += _strlen(shell_d->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
/**
 * err_exit_shell - error message for exiting in the getexit func
 * @shell_d: structure containing relevant data
 *
 * Return: Always a pointer
 */
char *err_exit_shell(shell_data *shell_d)
{
	int len;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(shell_d->counter);
	len = _strlen(shell_d->av[0]) + _strlen(ver_str);
	len += _strlen(shell_d->args[0]) + _strlen(shell_d->args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shell_d->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_d->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, shell_d->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
/**
 * err_get_cd - err msg for the cd command in getcd
 * @shell_d: relevant data structure
 * Return: the error msg to display
 */
char *err_get_cd(shell_data *shell_d)
{
	int len, length_id;
	char *error, *ver_str, *message;

	ver_str = aux_itoa(shell_d->counter);
	if (shell_d->args[1][0] == '-')
	{
		message = ": Illegal option ";
		length_id = 2;
	}
	else
	{
		message = ": can't cd to ";
		length_id = _strlen(shell_d->args[1]);
	}

	len = _strlen(shell_d->av[0]) + _strlen(shell_d->args[0]);
	len += _strlen(ver_str) + _strlen(message) + length_id + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = _strcat_cd(shell_d, message, error, ver_str);

	free(ver_str);

	return (error);
}
/**
 * _strcat_cd - to concatenate the cd error msg
 * @shell_d: the relevant data structure
 * @mesage: the msg to be printed
 * @error: the message outputed
 * @ver_str: to count the lines
 * Return: Always a pointer
 */

char *_strcat_cd(shell_data *shell_d, char *mesage, char *error, char *ver_str)
{
	char *illegal_flg;

	_strcpy(error, shell_d->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_d->args[0]);
	_strcat(error, mesage);
	if (shell_d->args[1][0] == '-')
	{
		illegal_flg = malloc(3);
		illegal_flg[0] = '-';
		illegal_flg[1] = shell_d->args[1][1];
		illegal_flg[2] = '\0';
		_strcat(error, illegal_flg);
		free(illegal_flg);
	}
	else
	{
		_strcat(error, shell_d->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}
/**
 * aux_itoa - to convert an integer to a string
 * @num: the int type number
 * Return: Always a string
 */
char *aux_itoa(int num)
{
	unsigned int num1;
	int len = obt_len(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		*(buffer + len) = (num1 % 10) + '0';
		num1 = num1 / 10;
		len--;
	}
	while (num1 > 0)
		;
	return (buffer);
}
