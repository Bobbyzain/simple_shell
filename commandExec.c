#include "main.h"

/**
 * execute_command - to execute user commands
 * @argv: the argument vector
 * Return: Always int
 */

int execute_command(char **argv)
{
	char *command = NULL, *actual_cmd = NULL;
	pid_t child_pid;
	int status;

	child_pid = fork(); /* Fork a child process */
	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (child_pid == 0) /* This is a child process */
	{
		if (argv)
		{
			command = argv[0]; /* obtain command */
			actual_cmd = get_loc(command); /*generate path before passing*/
			if (execve(actual_cmd, argv, NULL) == -1)
			{
				perror("Error:");
			}
		}
	}
	else /* This is a parent process */
		wait(&status);/* Waiting for the child process to complete */
	return (status);
}
/**
 * exit_shell - to exit the shell
 * @dsh: the relevant data
 * Return: Always int
 */
int exit_shell(shell_data *dsh)
{
	unsigned int uint_status; /* default exit status */
	int is_num, str_length, big_num;

	if (dsh->args[1] != NULL)
	{
		uint_status = _atoi(dsh->args[1]);
		is_num =  _isdigit(dsh->args[1]);
		str_length = _strlen(dsh->args[1]);
		big_num = uint_status > (unsigned int)INT_MAX;
		if (!is_num || str_length > 10 || big_num)
		{
			/*obt_error(dsh, 2);*/
			dsh->status = 2;
			return (1);
		}
		dsh->status = (uint_status % 256);
	}
	return (0);
}
