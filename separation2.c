#include "main.h"
/**
 * _swap_char - swaps | and & for non-printed chars
 *
 * @string: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *_swap_char(char *string, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; string[i]; i++)
		{
			if (string[i] == '|')
			{
				if (string[i + 1] != '|')
					string[i] = 16;
				else
					i++;
			}

			if (string[i] == '&')
			{
				if (string[i + 1] != '&')
					string[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; string[i]; i++)
		{
			string[i] = (string[i] == 16 ? '|' : string[i]);
			string[i] = (string[i] == 12 ? '&' : string[i]);
		}
	}
	return (string);
}

/**
 * _add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @string: input string
 * Return: no return
 */
void _add_nodes(sepL **head_s, lineL **head_l, char *string)
{
	int i;
	char *line;

	string = _swap_char(string, 0);

	for (i = 0; string[i]; i++)
	{
		if (string[i] == ';')
			add_sep_node_end(head_s, string[i]);

		if (string[i] == '|' || string[i] == '&')
		{
			add_sep_node_end(head_s, string[i]);
			i++;
		}
	}

	line = _strtok(string, ";|&");
	do {
		line = _swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shell_d: data structure
 * Return: no return
 */
void _go_next(sepL **list_s, lineL **list_l, shell_data *shell_d)
{
	int loop_separator;
	sepL *ls_s;
	lineL *ls_l;

	loop_separator = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_separator)
	{
		if (shell_d->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_separator = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_separator = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_separator)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * _split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @shell_d: data structure
 * @string: input string
 * Return: 0 to exit, 1 to continue
 */
int _split_commands(shell_data *shell_d, char *string)
{

	sepL *head_s, *list_s;
	lineL *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	_add_nodes(&head_s, &head_l, string);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shell_d->input = list_l->line;
		shell_d->args = _split_line(shell_d->input);
		loop = _execution_line(shell_d);
		free(shell_d->args);

		if (loop == 0)
			break;

		_go_next(&list_s, &list_l, shell_d);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * _split_line - tokenizes the input string
 *
 * @string: input string.
 * Return: string splitted.
 */
char **_split_line(char *string)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFFERSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(string, TOK_DELIMITER);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFFERSIZE;
			tokens = _realocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIMITER);
		tokens[i] = token;
	}

	return (tokens);
}
