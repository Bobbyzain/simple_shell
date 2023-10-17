#include "main.h"
int strtok_test(void)
{
        char *token;
        char **argv = NULL;
        int i, j;

        token = _strtok("This life go better", " "); /* Store each token in the argv array */
        for (i = 0; token != NULL; i++)
        {
                argv[i] = malloc(sizeof(char) * strlen(token));
                strcpy(argv[i], token);
                token = _strtok(NULL, " ");
        }
        argv[i] = NULL;
        for (j = 0; argv[j] != NULL; j++)
                printf("%s\n", argv[j]);
        return (0);
}

