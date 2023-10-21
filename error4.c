#include "main.h"

/**
 * rep_char - counts the repetitions of a char
 *
 * @str: input string
 * @ind: index
 * Return: repetitions
 */
int rep_char(char *str, int ind)
{
	if (*(str - 1) == *str)
		return (rep_char(str - 1, ind + 1));

	return (ind);
}

/**
 * _error_sep_op - finds syntax errors
 *
 * @str: input string
 * @ind: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int _error_sep_op(char *str, int ind, char last)
{
	int count;

	count = 0;
	if (*str == '\0')
		return (0);

	if (*str == ' ' || *str == '\t')
		return (_error_sep_op(str + 1, ind + 1, last));

	if (*str == ';')
		if (last == '|' || last == '&' || last == ';')
			return (ind);

	if (*str == '|')
	{
		if (last == ';' || last == '&')
			return (ind);

		if (last == '|')
		{
			count = rep_char(str, 0);
			if (count == 0 || count > 1)
				return (ind);
		}
	}

	if (*str == '&')
	{
		if (last == ';' || last == '|')
			return (ind);

		if (last == '&')
		{
			count = rep_char(str, 0);
			if (count == 0 || count > 1)
				return (ind);
		}
	}

	return (_error_sep_op(str + 1, ind + 1, *str));
}

/**
 * first_char - finds index of the first char
 *
 * @str: input string
 * @ind: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *str, int *ind)
{

	for (*ind = 0; str[*ind]; *ind += 1)
	{
		if (str[*ind] == ' ' || str[*ind] == '\t')
			continue;

		if (str[*ind] == ';' || str[*ind] == '|' || str[*ind] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_err - prints when a syntax error is found
 *
 * @shell_d: data structure
 * @str: input string
 * @ind: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_err(shell_data *shell_d, char *str, int ind, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (str[ind] == ';')
	{
		if (bool == 0)
			msg = (str[ind + 1] == ';' ? ";;" : ";");
		else
			msg = (str[ind - 1] == ';' ? ";;" : ";");
	}

	if (str[ind] == '|')
		msg = (str[ind + 1] == '|' ? "||" : "|");

	if (str[ind] == '&')
		msg = (str[ind + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(shell_d->counter);
	length = _strlen(shell_d->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, shell_d->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_err - intermediate func to
 * find and print a syntax error
 *
 * @shell_d: the data structure
 * @str: input string
 * Return: 1 if error. 0 in other case
 */
int check_syntax_err(shell_data *shell_d, char *str)
{
	int begin = 0;
	int f_char = 0;
	int ind = 0;

	f_char = first_char(str, &begin);
	if (f_char == -1)
	{
		print_syntax_err(shell_d, str, begin, 0);
		return (1);
	}

	ind = _error_sep_op(str + begin, 0, *(str + begin));
	if (ind != 0)
	{
		print_syntax_err(shell_d, str, begin + ind, 1);
		return (1);
	}

	return (0);
}
