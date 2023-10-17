#include "main.h"

/**
 * execute_command - the command execution function
 * @command: the command that needs to be executed
 * Return: Always int
 */

int execute_command(char *command)
{
	char *cmd = NULL;
	pid_t child_pid;
	int status, arg_count = 0;
	char *token, *args[BUFFERSIZE];
	/*char full_path[BUFFERSIZE];*/

	child_pid = fork(); /* Fork a child process */
	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (child_pid == 0) /* This is a child process */
	{
		token = strtok(command, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;
		execve(args[0], args, NULL);
		perror("execve failed");
		exit(1);
		/*if (args[0][0] == '/')*/ /* Does command contain '/' indicating abs or rel PATH */
		/*{
			if (path_env != NULL)
			{*/
				/*strncpy(path_copy, path_env, sizeof(path_copy));*/
				/*dir = strtok(path_env, ":");
				while (dir != NULL)
				{
					sprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
					args[0] = full_path;
					if (execve(full_path, args, NULL) == -1) Try executing the command with the full path */
					/*{*/
						/* Continue searching in path */
					/*}
					token = strtok(NULL, ":");*/ /* Move to the next directory in PATH */
				/*}
			}
		}*/
		/*else
		{
			if (execve(args[0], args, NULL) == -1)
			{*/
				/*If execve fails, print an error message */
				/*perror(args[0]);
				exit(EXIT_FAILURE);
			}
		}
		exit(EXIT_FAILURE);*/
	}
	else /* This is a parent process */
		wait(&status);/* Waiting for the child process to complete */

	return (status);
}
