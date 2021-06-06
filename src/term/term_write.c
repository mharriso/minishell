#include <term.h>
#include "tstr.h"
#include "ft_term.h"
#include "term_utils.h"

void	term_eol_check(int cols, size_t len)
{
	if (((len + PROMPT_SIZE) % (cols - 1)) == 0)
	{
		tputs(cursor_down, 1, term_putchar);
		while (cols > 0)
		{
			tputs(cursor_left, 1, term_putchar);
			cols--;
		}
	}
	else
		tputs(cursor_right, 1, term_putchar);
}

void	term_del_char(t_string *str, size_t *pos, int cols)
{
	size_t	cur_pos;

	if (*pos)
	{
		tstr_remove_at(str, *pos);
		tputs(restore_cursor, 1, term_putchar);
		tputs(clr_eos, 1, term_putchar);
		write(1, str->str, str->pos);
		tputs(restore_cursor, 1, term_putchar);
		cur_pos = *pos;
		*pos = 0;
		while (cur_pos > 1)
		{
			term_eol_check(cols, *pos);
			(*pos)++;
			cur_pos--;
		}
	}
}

void	term_write( t_string *str, size_t *pos, t_string *buff, int cols)
{
	char	*end_part;
	size_t	elen;

	end_part = tstr_insert_size(str, *pos, buff->str, buff->len);
	tputs(restore_cursor, 1, term_putchar);
	write(1, str->str, str->pos);
	tputs(restore_cursor, 1, term_putchar);
	elen = ft_strlen(end_part);
	elen = str->pos - elen + 1;
	*pos = 0;
	while (elen > 0)
	{
		term_eol_check(cols, *pos);
		(*pos)++;
		elen--;
	}
}
