#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sepL.
 * @h: the head of the linked list.
 * @sept: separator found (; | &).
 * Return: address of the head.
 */
sepL *add_sep_node_end(sepL **h, char sept)
{
	sepL *new, *temp;

	new = malloc(sizeof(sepL));
	if (new == NULL)
		return (NULL);

	new->separator = sept;
	new->next = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*h);
}

/**
 * free_sep_list - frees a sepL
 * @h: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sepL **h)
{
	sepL *temp;
	sepL *cur;

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

/**
 * add_line_node_end - adds a command line at the end
 * of a lineL.
 * @h: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
lineL *add_line_node_end(lineL **h, char *line)
{
	lineL *new, *temp;

	new = malloc(sizeof(lineL));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*h);
}

/**
 * free_line_list - frees a lineL
 * @h: head of the linked list.
 * Return: no return.
 */
void free_line_list(lineL **h)
{
	lineL *temp;
	lineL *cur;

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
