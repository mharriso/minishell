#include "structs.h"

t_redir	red_create(char *fname, int type)
{
	t_redir	red;

	red.fname = fname;
	red.type = type;
	return (red);
}

t_redir	red_create_last()
{
	return (red_create(NULL, 0));
}
