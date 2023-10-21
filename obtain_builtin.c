#include "main.h"

/**
 * get_built_in - this pairs the command with the arguments
 * @command: the command in question
 * Return: Always a function pointer
 */
int (*get_built_in(char *command))(shell_data *)
{
	_builtint built_in[] = {
		{"exit", exit_shell},
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", change_d_shell },
		{ "help", get_help },
		{NULL, NULL}
	};
	int j;

	for (j = 0; built_in[j].name; j++)
	{
		if (_strcmp(built_in[j].name, command) == 0)
			break;
	}

	return (built_in[j].f);
}
