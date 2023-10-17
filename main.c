#include "main.h"

/**
 * main - Entry point
 * @argc: Variable count
 * @argv: Argument vector
 * Return: Always Int
 */

int main(int argc, char **argv)
{
	char *lnptr, *lnptr_copy = NULL, *token;
	const char *delim = " \n";
	ssize_t num;
	size_t n = 0;
	int i = 0;

	(void)argc; /* Declaring void variables */
	while (1) /* Our shell loop */
	{
		write(STDIN_FILENO, PROMPT, 9);
		num = _getline(&lnptr, &n, stdin); /* to get input from the user*/
		if (!lnptr)
			break; /* Exit on Ctrl+D (EOF) */
		if (num == -1)
		{
			printf("Exiting shell...");
			return (-1);
		}
		lnptr_copy = malloc(sizeof(char) * num); /* Allocating memory */
		if (lnptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(lnptr_copy, lnptr);
		token = _strtok(lnptr, delim); /*splits the input string*/
		main2(token, argv, lnptr_copy);
	}
	for (; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
	free(lnptr);
	free(lnptr_copy);
	return (0);
}
/**
 * main2 - continuation of main
 * @token: the tokenized string input
 * @argv: argument vector array passed
 * @lnptr_copy: copy of lnptr
 * Return: pointer to pointer to strings
 */
char **main2(char *token, char **argv, char *lnptr_copy)
{
	const char *delim = " \n";
	int num_t, i;
	char **env;

	while (token != NULL)
	{
		num_t++; /* determine the no of tokens */
		token = _strtok(NULL, delim);
	}
	num_t++;
	argv = malloc(sizeof(char *) * num_t);
	token = _strtok(lnptr_copy, delim); /* Store each token in the argv array */
	for (i = 0; token != NULL; i++)
	{
		free(argv[i]);
		argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(argv[i], token);
		token = _strtok(NULL, delim);
	}
	argv[i] = NULL;
	if (*argv[0] != '\0') /* check for empty input */
	{
		if (strcmp(argv[0], "exit") == 0)
		{
			exit(0); /* Handle the exit command */
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			env = environ;
			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else
			execute_command(argv); /* Execute the command */

	}
	return (argv);
}
