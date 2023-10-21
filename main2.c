#include "main.h"

/**
 * free_data - frees data structure
 *
 * @shell_d: data structure
 * Return: no return
 */
void free_data(shell_data *shell_d)
{
	unsigned int i;

	for (i = 0; shell_d->_environ[i]; i++)
	{
		free(shell_d->_environ[i]);
	}

	free(shell_d->_environ);
	free(shell_d->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @shell_d: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(shell_data *shell_d, char **av)
{
	unsigned int i;

	shell_d->av = av;
	shell_d->input = NULL;
	shell_d->args = NULL;
	shell_d->status = 0;
	shell_d->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	shell_d->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shell_d->_environ[i] = strdup(environ[i]);
	}

	shell_d->_environ[i] = NULL;
	shell_d->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shell_data shell_d;
	(void) ac;

	signal(SIGINT, _get_sigint);
	set_data(&shell_d, av);
	shell_loop(&shell_d);
	free_data(&shell_d);
	if (shell_d.status < 0)
		return (255);
	return (shell_d.status);
}

/**
 * w_o_comment - deletes comments from the jnput
 *
 * @string: input string
 * Return: input without comments
 */
char *w_o_comment(char *string)
{
	int j, up_to;

	up_to = 0;
	for (j = 0; string[j]; j++)
	{
		if (string[j] == '#')
		{
			if (j == 0)
			{
				free(string);
				return (NULL);
			}

			if (string[j - 1] == ' ' || string[j - 1] == '\t' || string[j - 1] == ';')
				up_to = j;
		}
	}

	if (up_to != 0)
	{
		string = _realloc(string, j, up_to + 1);
		string[up_to] = '\0';
	}

	return (string);
}

/**
 * shell_loop - Loop of shell
 * @shell_d: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(shell_data *shell_d)
{
	int looper, i_eof;
	char *input;

	looper = 1;
	while (looper == 1)
	{
		write(STDIN_FILENO, "cisfun $ ", 9);
		input = _read_line(&i_eof);
		if (i_eof != -1)
		{
			input = w_o_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_err(shell_d, input) == 1)
			{
				shell_d->status = 2;
				free(input);
				continue;
			}
			input = _rep_var(input, shell_d);
			looper = _split_commands(shell_d, input);
			shell_d->counter += 1;
			free(input);
		}
		else
		{
			looper = 0;
			free(input);
		}
	}
}
