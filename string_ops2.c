#include "main.h"

/**
 * _strcat - to concatenate strings
 * @d: the pointer to destination of the copied string
 * @source: pointer to the source string
 * Return: Always pointer
 */

char *_strcat(char *d, const char *source)
{
	int a;
	int b;

	for (a = 0; d[a] != '\0'; a++)
		;

	for (b = 0; source[b] != '\0'; b++)
	{
		d[a] = source[b];
		a++;
	}

	d[a] = '\0';
	return (d);
}
/**
 * _strcpy - to copy one string into another
 * @d: the pointer to the destination for storing copied str
 * @source: the source of the str to be copied
 * Return: Pointer to char
 */
char *_strcpy(char *d, char *source)
{

	size_t a;

	for (a = 0; source[a] != '\0'; a++)
	{
		d[a] = source[a];
	}
	d[a] = '\0';

	return (d);
}
/**
 * _strcmp - to compare to strings
 * @str1: the 1st str
 * @str2: the 2nd str
 * Return: Always 0
 */

int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}
/**
 * reverse_string - reverses a string.
 * @string: input string.
 * Return: no return.
 */
void reverse_string(char *string)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (string[count] == '\0')
			break;
		count++;
	}
	str = string;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
/**
 * _strdup - duplicates a str in the heap memory.
 * @str: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *str)
{
	char *new;
	size_t len;

	len = _strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, str, len + 1);
	return (new);
}
