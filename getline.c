#include "main.h"

/**
 * _getline - to get the line from user input stream
 * @linepointer: buffer to store user input
 * @n: no. of chars in lineptr
 * @stream: stream to read from
 * Return: structure of the user input string and length
 */

ssize_t _getline(char **linepointer, size_t *n, FILE *stream)
{
	int i;
	char c = 'z';
	static ssize_t rr;
	ssize_t retval;
	char *buffer = (char *)malloc(BUFFERSIZE);

	if (rr == 0)
		fflush(stream);
	else
		return (-1);
	if (buffer == NULL)
	{
		perror("malloc");
		return (-1);
	}
	while (c != '\n')
	{
		i = read(STDIN_FILENO, &c, 1);
		if (i == -1 || (i == 0 && rr == 0))
		{
			perror("Exiting shell...");
			free(buffer);
			return (-1);
		}
		if (i == 0 && rr != 0)
		{
			rr++;
			break;
		}
		if (rr >= BUFFERSIZE)
			buffer = _realloc(buffer, rr, rr + 1);/*Increase size*/
		buffer[rr] = c;
		rr++;
	}
	buffer[rr] = '\0';
	the_line(linepointer, n, buffer, rr);
	retval = rr;
	if (i != 0)
		rr = 0;
	return (retval);
}

/**
 * the_line - to assign the line variable to the _getline function
 * @lnptr: to store input str
 * @buf: the string that is being called
 * @n: size of the line
 * @buf_s: buffer size
 */

void the_line(char **lnptr, size_t *n, char *buf, size_t buf_s)
{
	if (*lnptr == NULL)
	{
		if (buf_s > BUFFERSIZE)
			*n = buf_s;
		else
			*n = BUFFERSIZE;
		*lnptr = buf;
	}
	else if (*n < buf_s)
	{
		if (buf_s > BUFFERSIZE)
			*n =  buf_s;
		else
			*n = BUFFERSIZE;
		*lnptr = buf;
	}
	else
	{
		strcpy(*lnptr, buf);
		free(buf);
	}
}
