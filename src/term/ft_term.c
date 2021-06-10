#include "ft_term.h"
#include "term_utils.h"
#include "history.h"
#include "exit.h"
#include "parser.h"
#include <term.h>

static t_string	*term_buf_init(void)
{
	t_string	*buf;

	buf = malloc(sizeof(t_string));
	if (!buf)
		error_exit("term_buf_init");
	buf->str = malloc(BUF_SIZE);
	if (!buf->str)
		error_exit("term_buf_init");
	buf->len = 0;
	term_clear_str(buf->str, BUF_SIZE);
	return (buf);
}

static void	term_keycode_handler(t_string *buf, t_string *line, \
							t_pos *pos, t_hisory *history)
{
	char	*his;

	if (!term_strcmp(buf->str, key_up))
	{
		his = history_up_arrow(&(history->cur));
		term_cur_vert(his, line, pos);
	}
	else if (!term_strcmp(buf->str, key_down))
	{
		his = history_down_arrow(&(history->cur), line->str);
		term_cur_vert(his, line, pos);
	}
	else if (!term_strcmp(buf->str, key_left))
		term_cur_left(&(pos->l), &(pos->r), pos->cols);
	else if (!term_strcmp(buf->str, key_right))
		term_cur_right(&(pos->l), &(pos->r), pos->cols);
	else if (*buf->str == '\x7f' || !term_strcmp(buf->str, key_backspace))
		term_del_char(line, &(pos->l), pos->cols);
	else if (*(buf->str) >= ' ' && *(buf->str) <= '~')
		term_write(line, &(pos->l), buf, pos->cols);
}

static int	term_line_handler(t_string *buf, t_string *line, \
								t_hisory *his)
{
	t_pos	pos;

	write(1, PROMPT, PROMPT_SIZE);
	tputs(save_cursor, 1, term_putchar);
	tstr_clear(line);
	pos.cols = tgetnum("co");
	pos.l = 0;
	pos.r = 0;
	term_clear_str(buf->str, BUF_SIZE);
	while (term_strcmp(buf->str, "\n") && \
			(term_strcmp(buf->str, "\4") || pos.l))
	{
		term_clear_str(buf->str, BUF_SIZE);
		buf->len = read(0, buf->str, BUF_SIZE);
		if (!term_strcmp(buf->str, "\003"))
			return (0);
		term_keycode_handler(buf, line, &pos, his);
	}
	return (1);
}

static void	term_free(t_string *buf, t_string *line, t_hisory *history)
{
	tstr_free(line);
	tstr_free(buf);
	history_free(history);
}

int	ft_term(char *pname, t_list **env)
{
	t_string		*buf;
	t_string		*line;
	t_hisory		*history;
	int				ret;

	history = history_init(pname, env);
	buf = term_buf_init();
	term_set_attr();
	line = tstr_create();
	while (term_strcmp(buf->str, "\4"))
	{
		if (!term_line_handler(buf, line, history))
			write(1, "\n", 1);
		else
		{
			if (*(line->str))
				history_add(history->fname, line->str, &(history->begin));
			history->cur = history->begin;
			write(1, "\n", 1);
			if (*(line->str))
				ret = run_parser(line->str, env);
		}
	}
	term_free(buf, line, history);
	return (ret);
}
