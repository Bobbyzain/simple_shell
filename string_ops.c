#include "main.h"

/**
 * _strtok - tokenizes strings passed into it
 * @str: The string to be tokenized
 * @delim: The delimiter character
 * Return: Pointer to the next token or NULL in the absence of more tokens
 */

char *_strtok(char str[], const char *delim)
{
	static char *save_ptr, *str_end;
	char *start;
	unsigned int i, j = 0;

	if (str != NULL)
	{
		if (char_comp(str, delim))
			return (NULL);
		save_ptr = str; /* To store the 1st address */
		i = _strlen(str);
		str_end = &str[i]; /* To store the last address */
	}
	start = save_ptr;
	if (start == str_end) /* if this is the end */
		return (NULL);
	for (j = 0; *save_ptr; save_ptr++)
	{
		/* Breaking our loop when next token is found */
		if (save_ptr != start)
			if (*save_ptr && *(save_ptr - 1) == '\0')
				break;
		/* Repplacing our delimeter for the null byte */
		for (i = 0; delim[i]; i++)
		{
			if (*save_ptr == delim[i])
			{
				*save_ptr = '\0';
				if (save_ptr == start)
					start++;
				break;
			}
		}
		if (j == 0 && *save_ptr)
			j = 1;
	}
	if (j == 0)
		return (NULL);
	return (start);
}
/**
 * _strlen - Returning the length of a string
 * @str: the pointer to the string
 * Return: Always int
 */
int _strlen(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
	}
	return (i);
}
/**
 * char_comp -  to compare characters within two strings
 * @s: the input string or 1st string
 * @delim: the delimiter
 *
 * Return: Always int
 */

int char_comp(char s[], const char *delim)
{
	unsigned int a, b, c;

	for (a = 0, c = 0; s[a]; a++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (s[a] == delim[b])
			{
				c++;
				break;
			}
		}
	}
	if (a == c)
		return (1);
	return (0);
}

/**
 * _atoi - converting a string to an integer
 * @str: the string to be converted
 * Return: Always int
 */
int _atoi(char *str)
{
	unsigned int num = 0, size = 0, a = 0, b = 1, c = 1, d;

	while (*(str + num) != '\0')
	{
		if (size > 0 && (*(str + num) < '0' || *(str + num) > '9'))
			break;
		if (*(str + num) == '-')
			b *= -1;

		if ((*(str + num) >= '0') && (*(str + num) <= '9'))
		{
			if (size > 0)
				c *= 10;
			size++;
		}
		num++;
	}
	for (d = num - size; d < num; d++)
	{
		a = a + ((*(str + d) - 48) * c);
		c /= 10;
	}
	return (a + b);
}

/**
 * _isdigit - to check if string passed is a number
 * @str: the input string
 * Return: Always int
 */

int _isdigit(const char *str)
{
	unsigned int a;

	for (a = 0; str[a]; a++)
	{
		if (str[a] < 48 || str[a] > 57)
			return (0);
	}
	return (1);
}
