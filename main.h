#ifndef MAIN_H
#define MAIN_H

/* HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>
#include <limits.h>
/* STRUCTURES */
typedef struct {
    char *line;
    ssize_t read_result;
} lineResult;

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

/* PROTOTYPES */
int execute_command(char **argv);
/*int main(void);*/
char *read_user_input(void);
char *_which(char *command, char *path);
char *_getenv(const char *name);
int main(int argc, char **argv);
char *get_loc(char *command);
/*void exit_shell(char **args);*/
char **main2(char *token, char **argv, char *lnptr_copy);
ssize_t _getline(char **linepointer, size_t *n, FILE *stream);
void *_realloc(void *old_ptr, unsigned int old_s, unsigned int new_s);
void _memcopy(void *new_ptr, const void *orig_ptr, unsigned int s);
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

/* GLOBAL VARIABLES */
#define BUFFERSIZE 1024
extern char **environ;
#define PROMPT "cisfun $ "

#endif /* MAIN_H */
