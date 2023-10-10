#include "main.h"

/**
 * _getenv - to obtain environment varaibles
 * @name: the name of the environment variable to search for
 * Return: pointer to char
 */

char *_getenv(const char *name)
{
	char *env_variable = getenv(name);

	if (env_variable == NULL)
		return (NULL);

	return (strdup(env_variable));
}
