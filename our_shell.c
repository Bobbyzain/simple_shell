#include "main.h"

/**
 * main - entry point to our shell
 * Return: Always int
 */

int main(void)
{
	char *command;

	while (1)
	{
		printf("cisfun$ "); /* Display a prompt */
		command = read_user_input(); /* Input reader function is implemented here */
		if (!command)
			break; /* Exit if Ctrl+D (EOF) is encountered */
		if (*command != '\0') /* Check for empty input */
			execute_command(command); /* Implement command execution function */
		free(command); /* Free allocated memory for the command */
	}

	return (0);
}
