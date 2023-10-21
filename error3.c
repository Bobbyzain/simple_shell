#include "main.h"

/**
 * obt_len - to obtain the length of a number
 * @num: the number whose we want
 * Return: length of num
 */

int obt_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 = num1 / 10;
	}

	return (len);
}



