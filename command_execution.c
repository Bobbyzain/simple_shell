#include "main.h"

/**
 * execute_command - the command execution function
 * @command: the command that needs to be executed
 * Return: Always int
 */

int execute_command(char *command)
{
	pid_t child_pid;
	int status, num = 0;
	char *args[BUFFERSIZE], *token;

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[num++] = token;
		token = strtok(NULL, " ");
	}
	args[num] = NULL; /* null-terminate the argument list */

	/* Fork a child process */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (child_pid == 0) /* This is a child process */
	{
		execve(command, args, NULL);

		/* If execve fails, print an error message */
		perror(command);
		exit(EXIT_FAILURE);
	}
	else /* This is a parent process */
	{
		/* Waiting for the child process to complete */
		wait(&status);
	}

	return (0);
}
