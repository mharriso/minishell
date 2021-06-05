#include "ft_term.h"
#include "term_utils.h"
#include "history.h"
#include <term.h>

#include <stdio.h> //REMOVE!!!

static t_string	*term_buf_init(void)
{
	t_string	*buf;

	buf = malloc(sizeof(t_string));
	if (!buf)
		exit(EXIT_FAILURE);
	buf->str = malloc(BUF_SIZE);
	if (!buf->str)
		exit(EXIT_FAILURE);
	buf->len = 0;
	term_clear_str(buf->str, BUF_SIZE);
	return (buf);
}

static void	term_set_attr(struct termios *orig)
{
	char			*term_name;
	struct termios	new;

	term_name = getenv("TERM");
	if (tgetent(0, term_name) != 1)
		exit(EXIT_FAILURE);
	if (tcgetattr(0, orig))
		exit(EXIT_FAILURE);
	new = *orig;
	new.c_lflag &= ~(ECHO | ICANON);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &new))
		exit(EXIT_FAILURE);
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
	else if (ft_strcmp(buf->str, "\033") && \
			term_strcmp(buf->str, "\n") && term_strcmp(buf->str, "\4"))
		term_write(line, &(pos->l), buf, pos->cols);
}

static void	term_line_handler(t_string *buf, t_string *line, \
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
		term_keycode_handler(buf, line, &pos, his);
	}
}

void	ft_term(char *pname, t_list **env)
{
	t_string		*buf;
	t_string		*line;
	t_hisory		*history;
	struct termios	orig;

	history = history_init(pname, env);
	buf = term_buf_init();
	term_set_attr(&orig);
	line = tstr_create();
	while (term_strcmp(buf->str, "\4"))
	{
		term_line_handler(buf, line, history);
		if (*(line->str))
			history_add(line->str, &(history->begin));
		history->cur = history->begin;
		write(1, "\n", 1);
		if (*(line->str))
			printf("line = |%s|\n", line->str); //parser
	}
	tstr_free(line);
	tstr_free(buf);
	history_save(history->fname, history->begin); // in success_exit
	history_free(history);
	tcsetattr(0, TCSANOW, &orig); //  in success_exit
}
