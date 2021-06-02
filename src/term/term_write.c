#include <term.h>
#include "tstr.h"
#include "ft_term.h"
#include "term_utils.h"

void	term_del_char(t_string *str, size_t *pos, int cols)
{
	if (*pos)
	{
		tstr_remove_at(str, *pos);
		term_cur_left_ol(cols, *pos);
		tputs(delete_character, 1, term_putchar);
		(*pos)--;
	}
}

void	term_write( t_string *str, size_t *pos, t_string *buff, int cols)
{
	char	*end_part;
	size_t	elen;

	end_part = tstr_insert_size(str, *pos, buff->str, buff->len);
	if (!end_part)
		write(1, buff->str, buff->len);
	else
	{
		ft_putstr_fd(end_part, 1);
		elen = ft_strlen(end_part);
		while (elen > 1)
		{
			term_cur_left_ol(cols, *pos);
			elen--;
		}
	}
	(*pos) += buff->len;
}
