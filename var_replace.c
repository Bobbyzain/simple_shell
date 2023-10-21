#include "main.h"
/**
 * add_rvar_node - adds a variable at the end
 * of a r_varL list.
 * @h: head of the linked list.
 * @var_len: length of the variable.
 * @value: value of the variable.
 * @value_len: length of the value.
 * Return: address of the head.
 */
r_varL *add_rvar_node(r_varL **h, int var_len, char *value, int value_len)
{
	r_varL *newer, *temp;

	newer = malloc(sizeof(r_varL));
	if (newer == NULL)
		return (NULL);

	newer->len_var = var_len;
	newer->val = value;
	newer->len_val = value_len;

	newer->next = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = newer;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newer;
	}

	return (*h);
}

/**
 * free_rvar_list - frees a r_varL list
 * @h: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(r_varL **h)
{
	r_varL *temp;
	r_varL *cur;

	if (h != NULL)
	{
		cur = *h;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*h = NULL;
	}
}
