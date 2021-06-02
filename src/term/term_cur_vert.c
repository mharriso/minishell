#include <term.h>
#include "tstr.h"
#include "ft_term.h"
#include "term_utils.h"

static void	term_write_history(const char *msg, t_string *str, size_t *pos)
{
	size_t	len;

	len = ft_strlen(msg);
	str->pos = 0;
	*(str->str) = '\0';
	tstr_add_size(str, msg, len);
	write(1, msg, len);
	*pos = len;
}

void	term_cur_vert(const char *str, t_string *line, size_t *pos)
{
	if (!str)
		return ;
	tputs(restore_cursor, 1, term_putchar);
	tputs(clr_eos, 1, term_putchar);
	term_write_history(str, line, pos);
}
