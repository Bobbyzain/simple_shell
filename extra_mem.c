#include "main.h"

/**
 * _memcpy - copies info between two void pointers
 * @new_ptr: destination pointer
 * @orig_ptr: source pointer.
 * @s: size of the new pointer.
 * Return: none
 */

void _memcpy(void *new_ptr, const void *orig_ptr, unsigned int s)
{
	char *one_origptr = (char *)orig_ptr;
	char *one_newptr = (char *)new_ptr;
	unsigned int i;

	for (i = 0; i < s; i++)
		one_newptr[i] = one_origptr[i];
}

/**
 * _realloc - to dynamically reallocate mem space
 * @old_ptr: previously allocated memory space
 * @old_s: size, in bytes, of the old memory block.
 * @new_s: new size of memory block.
 * Return: ptr
 */

void *_realloc(void *old_ptr, unsigned int old_s, unsigned int new_s)
{
	void *new_ptr;

	if (old_ptr == NULL)
		return (malloc(new_s));
	if (new_s == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	if (new_s == old_s)
		return (old_ptr);
	new_ptr = malloc(new_s);
	if (new_ptr == NULL)
		return (NULL);
	if (new_s < old_s)
		_memcpy(new_ptr, old_ptr, new_s);
	else
		_memcpy(new_ptr, old_ptr, old_s);
	free(old_ptr);
	return (new_ptr);
}
/**
 * _realocdp - reallocates a mem block of a double pointer.
 * @p: double pointer to the mem previously allocated.
 * @old_s: size, in bytes, of the allocated space of ptr.
 * @new_s: new size, in bytes, of the new mem block.
 *
 * Return: p.
 * if new_s == old_s, returns p without changes.
 * if malloc fails, returns NULL.
 */
char **_realocdp(char **p, unsigned int old_s, unsigned int new_s)
{
	char **newp;
	unsigned int i;

	if (p == NULL)
		return (malloc(sizeof(char *) * new_s));

	if (new_s == old_s)
		return (p);

	newp = malloc(sizeof(char *) * new_s);
	if (newp == NULL)
		return (NULL);

	for (i = 0; i < old_s; i++)
		newp[i] = p[i];

	free(p);

	return (newp);
}
