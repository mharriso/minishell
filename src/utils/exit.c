#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <term.h>
#include "g_var.h"

void	restor_params(void)
{
	if (tcsetattr(0, TCIFLUSH, &g_orig))
		printf("Error: restor_params\n");
}

void	error_exit(const char *msg)
{
	char	*errorbuf;

	errorbuf = strerror(errno);
	printf("%s: %s\n", msg, errorbuf);
	restor_params();
	exit(EXIT_FAILURE);
}

void	success_exit(char code)
{
	restor_params();
	exit(code);
}
