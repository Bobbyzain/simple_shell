#include "main.h"

/**
 * extra_help - Help information for the builtin help.
 * Return: no return
 */
void extra_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * extra_help_alias - Help information for the builtin alias.
 * Return: no return
 */
void extra_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * extra_help_cd - Help information for the builtin alias.
 * Return: no return
 */
void extra_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * get_help - function that retrieves help messages according builtin
 * @shell_d: data structure (args and input)
 * Return: Return 0
*/
int get_help(shell_data *shell_d)
{

	if (shell_d->args[1] == 0)
		extra_help_general();
	else if (_strcmp(shell_d->args[1], "setenv") == 0)
		extra_help_setenv();
	else if (_strcmp(shell_d->args[1], "env") == 0)
		extra_help_env();
	else if (_strcmp(shell_d->args[1], "unsetenv") == 0)
		extra_help_unsetenv();
	else if (_strcmp(shell_d->args[1], "help") == 0)
		extra_help();
	else if (_strcmp(shell_d->args[1], "exit") == 0)
		extra_help_exit();
	else if (_strcmp(shell_d->args[1], "cd") == 0)
		extra_help_cd();
	else if (_strcmp(shell_d->args[1], "alias") == 0)
		extra_help_alias();
	else
		write(STDERR_FILENO, shell_d->args[0],
		      _strlen(shell_d->args[0]));

	shell_d->status = 0;
	return (1);
}
