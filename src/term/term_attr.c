#include <term.h>
#include <stdio.h>
#include "exit.h"
#include "ft_term.h"

static struct termios	g_orig;

void	restor_params(void)
{
	if (tcsetattr(0, TCIFLUSH, &g_orig))
		printf("Error: restor_params\n");
}

void	term_set_attr(void)
{
	char			*term_name;
	struct termios	new;

	term_name = getenv("TERM");
	if (tgetent(0, term_name) != 1)
		error_exit("term_set_attr");
	if (tcgetattr(0, &g_orig))
		error_exit("term_set_attr");
	new = g_orig;
	new.c_lflag &= ~(ECHO | ICANON | ISIG);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &new))
		error_exit("term_set_attr");
}
