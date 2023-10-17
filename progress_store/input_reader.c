#include "main.h"

/**
 * read_user_input - to get the input from the shell user
 * Return: a char pointer to the input
 */

char *read_user_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&input, &len, stdin);
	if (read == -1)
	{
		if (feof(stdin))
		{
			/* Ctrl+D (EOF) detected, exiting */
			free(input);
			return (NULL);
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	/* Removing the newline character at the end, if present */
	if (input[read - 1] == '\n')
		input[read - 1] = '\0';

	return (input);
}
