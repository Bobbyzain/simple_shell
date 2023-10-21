#include "main.h"

/**
 * change_d_shell - to change the current directory
 * @shell_d: the relevant data
 * Return: Always 1
 */
int change_d_shell(shell_data *shell_d)
{
	char *directory;
	int is_home, is_home2, is_ddash;

	directory = shell_d->args[1];

	if (directory != NULL)
	{
		is_home = _strcmp("$HOME", directory);
		is_home2 = _strcmp("~", directory);
		is_ddash = _strcmp("--", directory);
	}

	if (directory == NULL || !is_home || !is_home2 || !is_ddash)
	{
		change_d_to_home(shell_d);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		change_d_previous(shell_d);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		change_d_dot(shell_d);
		return (1);
	}

	change_d_to(shell_d);

	return (1);
}
/**
 * change_d_dot - changes current to the parent directory
 *
 * @shell_d: data relevant (environ)
 *
 * Return: doesn't return
 */
void change_d_dot(shell_data *shell_d)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_environment("OLDPWD", cp_pwd, shell_d);
	directory = shell_d->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_environment("PWD", cp_pwd, shell_d);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	reverse_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			reverse_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_environment("PWD", cp_strtok_pwd, shell_d);
	}
	else
	{
		chdir("/");
		set_environment("PWD", "/", shell_d);
	}
	shell_d->status = 0;
	free(cp_pwd);
}

/**
 * change_d_to - changes to a given dir
 * by the user
 *
 * @shell_d: data relevant (directories)
 * Return: no return
 */
void change_d_to(shell_data *shell_d)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	directory = shell_d->args[1];
	if (chdir(directory) == -1)
	{
		obt_error(shell_d, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_environment("OLDPWD", cp_pwd, shell_d);

	cp_dir = _strdup(directory);
	set_environment("PWD", cp_dir, shell_d);

	free(cp_pwd);
	free(cp_dir);

	shell_d->status = 0;

	chdir(directory);
}

/**
 * change_d_previous - changes to the previous dir
 *
 * @shell_d: data relevant (environ)
 * Return: no return
 */
void change_d_previous(shell_data *shell_d)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenvironment("OLDPWD", shell_d->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_environment("OLDPWD", cp_pwd, shell_d);

	if (chdir(cp_oldpwd) == -1)
		set_environment("PWD", cp_pwd, shell_d);
	else
		set_environment("PWD", cp_oldpwd, shell_d);

	p_pwd = _getenvironment("PWD", shell_d->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shell_d->status = 0;

	chdir(p_pwd);
}

/**
 * change_d_to_home - changes to home dir
 *
 * @shell_d: data relevant (environ)
 * Return: no return
 */
void change_d_to_home(shell_data *shell_d)
{
	char *p_pwd, *homer;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	homer = _getenvironment("HOME", shell_d->_environ);

	if (homer == NULL)
	{
		set_environment("OLDPWD", p_pwd, shell_d);
		free(p_pwd);
		return;
	}

	if (chdir(homer) == -1)
	{
		obt_error(shell_d, 2);
		free(p_pwd);
		return;
	}

	set_environment("OLDPWD", p_pwd, shell_d);
	set_environment("PWD", homer, shell_d);
	free(p_pwd);
	shell_d->status = 0;
}
