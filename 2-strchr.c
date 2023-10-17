#include "main.h"

/**
 * _strchr - My string parsing function
 * Description: To find & return a pointer 'r' to a character within a string
 * @s: Pointer to the string I want to parse through
 * @c: The character whose occurence I am searching for
 * Return: Pointer to the 1st occurence of c in s else NULL
 */

char *_strchr(char *s, const char c)
{
	int i = 0;
	char *r;

	for (; s[i] != '\0'; i++)
	{
		if (s[i] == c)
		{
			r = &s[i];
			break;
		}
		else
		{
			continue;
		}
		r = "NULL";
	}
	return (r);
}
