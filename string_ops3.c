#include "main.h"

/**
 * _strspn - gets the len of a prefix substring.
 * @string: initial segment of the string.
 * @accept: the accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *string, char *accept)
{
	int i, j, bool;

	for (i = 0; *(string + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(string + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}

/**
 * _check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @str: input string
 * @data: data structure
 * Return: no return
 */
void _check_env(r_varL **h, char *str, shell_data *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (str[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; str[j]; j++)
	{
		if (str[j] == ' ' || str[j] == '\t' || str[j] == ';' || str[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * _check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @string: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int _check_vars(r_varL **h, char *string, char *st, shell_data *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; string[i]; i++)
	{
		if (string[i] == '$')
		{
			if (string[i + 1] == '?')
				add_rvar_node(h, 2, st, lst), i++;
			else if (string[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (string[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (string[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (string[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (string[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (string[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				_check_env(h, string + i, data);
		}
	}

	return (i);
}

/**
 * _replaced_input - replaces string into variables
 *
 * @h: head of the linked list
 * @string: input string
 * @new_string: new input string (replaced)
 * @new_len: new length
 * Return: replaced string
 */
char *_replaced_input(r_varL **h, char *string, char *new_string, int new_len)
{
	r_varL *ind;
	int i, j, k;

	ind = *h;
	for (j = i = 0; i < new_len; i++)
	{
		if (string[j] == '$')
		{
			if (!(ind->len_var) && !(ind->len_val))
			{
				new_string[i] = string[j];
				j++;
			}
			else if (ind->len_var && !(ind->len_val))
			{
				for (k = 0; k < ind->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < ind->len_val; k++)
				{
					new_string[i] = ind->val[k];
					i++;
				}
				j += (ind->len_var);
				i--;
			}
			ind = ind->next;
		}
		else
		{
			new_string[i] = string[j];
			j++;
		}
	}

	return (new_string);
}

/**
 * _rep_var - calls functions to replace string into vars
 *
 * @string: input string
 * @shell_d: data structure
 * Return: replaced string
 */
char *_rep_var(char *string, shell_data *shell_d)
{
	r_varL *head, *ind;
	char *status, *new_string;
	int old_len, new_len;

	status = aux_itoa(shell_d->status);
	head = NULL;

	old_len = _check_vars(&head, string, status, shell_d);

	if (head == NULL)
	{
		free(status);
		return (string);
	}

	ind = head;
	new_len = 0;

	while (ind != NULL)
	{
		new_len += (ind->len_val - ind->len_var);
		ind = ind->next;
	}

	new_len += old_len;

	new_string = malloc(sizeof(char) * (new_len + 1));
	new_string[new_len] = '\0';

	new_string = _replaced_input(&head, string, new_string, new_len);

	free(string);
	free(status);
	free_rvar_list(&head);

	return (new_string);
}
