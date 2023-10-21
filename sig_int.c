#include "main.h"

/**
 * _get_sigint - Handle the crtl + c call in prompt
 * @signals: Signal handler
 */
void _get_sigint(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\ncisfun ", 8);
}
