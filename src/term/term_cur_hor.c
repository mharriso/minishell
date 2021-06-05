#include <term.h>
#include "tstr.h"
#include "ft_term.h"
#include "term_utils.h"

void	term_cur_right_nl(int cols, size_t len, int is_write)
{
	if (((len + PROMPT_SIZE) % cols) == 0)
	{
		tputs(cursor_down, 1, term_putchar);
		while (cols > 0)
		{
			tputs(cursor_left, 1, term_putchar);
			cols--;
		}
	}
	else if (!is_write)
		tputs(cursor_right, 1, term_putchar);
}

void	term_cur_left_ol(int cols, size_t pos)
{
	if (((pos + PROMPT_SIZE) % cols) == 0)
	{
		tputs(cursor_up, 1, term_putchar);
		while (cols > 0)
		{
			tputs(cursor_right, 1, term_putchar);
			cols--;
		}
	}
	else
		tputs(cursor_left, 1, term_putchar);
}

void	term_cur_left(size_t *pos, size_t *posr, int cols)
{
	if (!(*pos))
		return ;
	term_cur_left_ol(cols, *pos);
	(*pos)--;
	(*posr)++;
}

void	term_cur_right(size_t *pos, size_t *posr, int cols)
{
	if (!(*posr))
		return ;
	term_cur_right_nl(cols, *pos + 1, 0);
	(*pos)++;
	(*posr)--;
}
