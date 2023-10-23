#ifndef _MAIN_H
#define _MAIN_H

/* HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <limits.h>

/* GLOBAL VARIABLES */
#define BUFFERSIZE 1024
extern char **environ;
#define TOK_BUFFERSIZE 128
#define TOK_DELIMITER " \t\r\n\a"
#define PROMPT "cisfun $ "

/* STRUCTURES */
/**
 * struct LR - struct to contain data for line resulsts
 * @line: the line from the user
 * @read_result: the number of chars read
 */
typedef struct LR
{
	char *line;
	ssize_t read_result;
} lineResult;

/**
 * struct my_data - struct that contains all relevant data
 * @av: argument vectors
 * @input: command line from user
 * @args: tokens of the cmd line
 * @status: last status of our shell
 * @counter: lines counter
 * @_environ: the environment variable
 * @pid: the shell's process ID
 */
typedef struct my_data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell_data;

/**
 * struct _builtins - struct that contains builtins
 * @name: the builtin command name
 * @f: the function pointer type
 */
typedef struct _builtins
{
	char *name;
	int (*f)(shell_data *shell_d);
} _builtint;

/**
 * struct sep_lists - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_lists
{
	char separator;
	struct sep_lists *next;
} sepL;
/**
 * struct line_lists - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_lists
{
	char *line;
	struct line_lists *next;
} lineL;

/**
 * struct rvar_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct rvar_list
{
	int len_var;
	char *val;
	int len_val;
	struct rvar_list *next;
} r_varL;

/* PROTOTYPES */
int execute_command(char **argv);
char *read_user_input(void);
/*char *_which(char *command, char *path);*/
/*char *_getenv(const char *name);*/
int main(int argc, char **argv);
char *get_loc(char *command);
char **main2(char *token, char **argv, char *lnptr_copy);
ssize_t _getline(char **linepointer, size_t *n, FILE *stream);
void *_realloc(void *old_ptr, unsigned int old_s, unsigned int new_s);
void _memcpy(void *new_ptr, const void *orig_ptr, unsigned int s);
void the_line(char **lnptr, size_t *n, char *buf, size_t buf_s);
char *_strtok(char *str, const char *delim);
int strtok_test(void);
int _strlen(const char *str);
char *_strchr(char s[], const char c);
int char_comp(char s[], const char *delim);
int in_currentdir(char *path, int *j);
int _atoi(char *str);
int _isdigit(const char *str);
int exit_shell(shell_data *dsh);
int obt_error(shell_data *shell_d, int err_val);
char *error_environment(shell_data *shell_d);
char *error_path126(shell_data *shell_d);
char *error_not_f(shell_data *shell_d);
char *err_exit_shell(shell_data *shell_d);
char *err_get_cd(shell_data *shell_d);
char *_strcat_cd(shell_data *shell_d, char *mesage, char *error, char *ver_s);
char *aux_itoa(int num);
int obt_len(int num);
int (*get_built_in(char *command))(shell_data *);
char *_strcat(char *d, const char *source);
char *_strcpy(char *d, char *source);
int _strcmp(char *str1, char *str2);
void free_data(shell_data *shell_d);
void set_data(shell_data *shell_d, char **av);
int main(int ac, char **av);
char *error_st(char **args);
char *error_perm(char **args);
int change_d_shell(shell_data *shell_d);
void change_d_dot(shell_data *shell_d);
void change_d_to(shell_data *shell_d);
void change_d_previous(shell_data *shell_d);
void change_d_to_home(shell_data *shell_d);
char *info_copy(char *name, char *val);
void set_environment(char *name, char *val, shell_data *shell_d);
int _setenv(shell_data *shell_d);
int _unsetenv(shell_data *shell_d);
int compare_env_name(const char *env_name, const char *name);
char *_getenvironment(const char *n, char **_environ);
int _env(shell_data *shell_d);
void reverse_string(char *string);
char *_strdup(const char *str);
char **_realocdp(char **p, unsigned int old_s, unsigned int new_s);
int _strspn(char *string, char *accept);
lineL *add_line_node_end(lineL **h, char *line);
void free_sep_list(sepL **h);
sepL *add_sep_node_end(sepL **h, char sept);
r_varL *add_rvar_node(r_varL **h, int var_len, char *value, int value_len);
void free_rvar_list(r_varL **h);
void free_line_list(lineL **h);
int rep_char(char *str, int ind);
int _error_sep_op(char *str, int ind, char last);
int first_char(char *str, int *ind);
void print_syntax_err(shell_data *shell_d, char *str, int ind, int bool);
int check_syntax_err(shell_data *shell_d, char *str);
void shell_loop(shell_data *shell_d);
char *w_o_comment(char *string);
char *_read_line(int *i_eof);
ssize_t get_line(char **lineptr, size_t *size, FILE *stream);
void bring_line(char **lineptr, size_t *size, char *buffer, size_t j);
char *_rep_var(char *string, shell_data *shell_d);
char *_replaced_input(r_varL **h, char *string, char *new_string, int new_len);
void _check_env(r_varL **h, char *str, shell_data *data);
int _check_vars(r_varL **h, char *string, char *st, shell_data *data);
void _get_sigint(int signals);
void extra_help_exit(void);
void extra_help_general(void);
void extra_help_unsetenv(void);
void extra_help_setenv(void);
void extra_help_env(void);
void extra_help_cd(void);
void extra_help_alias(void);
void extra_help(void);
int get_help(shell_data *shell_d);
int _execution_line(shell_data *shell_d);
int cmd_exec(shell_data *shell_d);
int check_error_cmd(char *directory, shell_data *shell_d);
int is_executable(shell_data *shell_d);
char *_which(char *cmd, char **_environ);
int is_current_dir(char *path, int *i);
char **_split_line(char *string);
int _split_commands(shell_data *shell_d, char *string);
void _go_next(sepL **list_s, lineL **list_l, shell_data *shell_d);
void _add_nodes(sepL **head_s, lineL **head_l, char *string);
char *_swap_char(char *string, int bool);


#endif /* MAIN_H */
