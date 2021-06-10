#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "ft_term.h"

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
