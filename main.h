#ifndef MAIN_H
#define MAIN_H

/* HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* PROTOTYPES */
int execute_command(char *command);
int main(void);
char *read_user_input(void);
char *_which(char *command, char *path);
char *_getenv(const char *name);

/* STRUCTURES */

/* GLOBAL VARIABLES */
#define BUFFERSIZE 1024

#endif /* MAIN_H */
