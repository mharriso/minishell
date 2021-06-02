#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"
//#include "history.h"

#include <signal.h>

#define PROMPT "minishell: "
#define PROMPT_SIZE 11
#define BUF_SIZE 8

typedef struct s_pos
{
	size_t	l;
	size_t	r;
}				t_pos;


typedef struct	s_string
{
	char	*str;
	size_t	len;
	size_t	pos;
}				t_string;

void	tstr_init(t_string *string)
{
	string->len = 4;
	string->str = malloc(string->len + 1);
	*(string->str) = '\0';
	string->pos = 0;
}

t_string	*tstr_create()
{
	t_string	*string;

	string = malloc(sizeof(t_string));
	if (!string)
		exit(EXIT_FAILURE);
	tstr_init(string);
	return (string);
}

void	tstr_clear(t_string *str)
{
	free(str->str);
	tstr_init(str);
}

void tstr_free(t_string *str)
{
	free(str->str);
	free(str);
}

void	tstr_resize(t_string *str, size_t len)
{
	char	*temp;

	while ((len + str->pos) > str->len)
			str->len <<= 1;
	temp = str->str;
	str->str = malloc(str->len + 1);
	ft_memcpy(str->str, temp, str->pos + 1);
	free(temp);
}

void	tstr_add_size(t_string *str, const char *src, size_t len)
{
	char	*temp;

	if ((len + str->pos) > str->len)
		tstr_resize(str, len);
	ft_strlcat(str->str, src, len + str->pos + 1);
	str->pos += len;
}

void	tstr_add(t_string *str, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	tstr_add_size(str, src, len);
}

//return pointer to str at the start of src
char*	tstr_insert_size(t_string *str, size_t pos, const char *src, size_t size)
{
	char *str_end;
	size_t len;

	if (pos == str->pos)
	{
		tstr_add_size(str, src, size);
		return (NULL);
	}
	len = ft_strlen(str->str);
	if ((len + size) > str->len)
		tstr_resize(str, size);
	while (len >= pos)
	{
		(str->str)[len + size] = (str->str)[len];
		if (len == 0)
			break ;
		len--;
	}
	ft_memcpy(&((str->str)[pos]), src, size);
	str->pos += size;
	return (&((str->str)[pos]));
}

void	tstr_insert(t_string *str, size_t pos, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	tstr_insert_size(str, pos, src, len);
}

void	tstr_remove(t_string *str)
{
	if (str->pos < 1)
		return ;
	str->pos--;
	str->str[str->pos] = '\0';
}

void	tstr_remove_at(t_string *str, size_t pos)
{
	size_t	len;

	if (pos == str->pos)
	{
		tstr_remove(str);
		return ;
	}
	len = ft_strlen(&((str->str)[pos - 1]));
	str->pos--;
	ft_memcpy(&((str->str)[pos - 1]),&((str->str)[pos]), len);
}

int	ft_putchar(int c)
{
	int res;
	res = write(1, &c, 1);
	return (0);
}

void	clear_str(char *str, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
}

int	term_strcmp(const char *s1, const char *s2)
{
	size_t i;
	int res;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == '[' && s2[i] == 'O')
		{
			i++;
			continue ;
		}
		if (s1[i] != s2[i])
		{
			res = s1[i] - s2[i];
			return (res);
		}
		i++;
	}
	return (0);
}

// void	term_cur_right_mr(int cols, size_t pos, size_t len)
// {
// 	int i;
// 	int res;

// 	if (((len + PROMPT_SIZE) % cols) == 0)
// 	{
// 		tputs(cursor_down, 1, ft_putchar);
// 		tputs(cursor_up, 1, ft_putchar);
// 		i = 0;
// 		while (i < pos + PROMPT_SIZE + 6)
// 		{
// 			tputs(cursor_right, 1, ft_putchar);
// 			i++;;
// 		}
// 	}
// }

void	term_cur_right_nl(int cols, size_t len, int is_write)
{
	if (((len + PROMPT_SIZE) % cols) == 0)
	{
		tputs(cursor_down, 1, ft_putchar);
		while (cols > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			cols--;
		}
	}
	else if (!is_write)
		tputs(cursor_right, 1, ft_putchar);
}

void	term_cur_left_ol(int cols, size_t pos)
{
	if (((pos + PROMPT_SIZE) % cols) == 0)
	{
		tputs(cursor_up, 1, ft_putchar);
		while (cols > 0)
		{
			tputs(cursor_right, 1, ft_putchar);
			cols--;
		}
	}
	else
		tputs(cursor_left, 1, ft_putchar);
}

void	term_del_char(t_string *str, size_t *pos, int cols)
{
	if (*pos)
	{
		tstr_remove_at(str, *pos);
		term_cur_left_ol(cols, *pos);
		tputs(delete_character, 1, ft_putchar);
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

void	term_write_history(const char *msg, t_string *str, size_t *pos)
{
	size_t	len;

	len = ft_strlen(msg);
	str->pos = 0;
	*(str->str) = '\0';
	tstr_add_size(str, msg, len);
	write(1, msg, len);
	*pos = len;
}

void	term_cur_left(t_string *str, size_t *pos, size_t *posr, int cols)
{
	if (!(*pos))
		return ;
	term_cur_left_ol(cols, *pos);
	(*pos)--;
	(*posr)++;
}

void	term_cur_right(t_string *str, size_t *pos, size_t *posr, int cols)
{
	if (!(*posr))
		return ;
	term_cur_right_nl(cols, *pos + 1, 0);
	(*pos)++;
	(*posr)--;
}

void	term_cur_vert( const char *str, t_string *line, size_t *pos)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eos, 1, ft_putchar);
	term_write_history(str, line, pos);
}

t_string *term_buf_init()
{
	t_string *buf;

	buf = malloc(sizeof(t_string));
	if (!buf)
		exit(EXIT_FAILURE);
	buf->str = malloc(BUF_SIZE);
	if (!buf->str)
		exit(EXIT_FAILURE);
	buf->len = 0;
	clear_str(buf->str, BUF_SIZE);
	return (buf);
}

void term_set_attr(struct termios *orig)
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

void	term_keycode_handler(t_string *buf, t_string *line, int cols, t_pos *pos)
{
	if (!term_strcmp(buf->str, key_up))
		term_cur_vert("up", line, &(pos->l));
	else if (!term_strcmp(buf->str, key_down))
		term_cur_vert("down", line, &(pos->l));
	else if (!term_strcmp(buf->str, key_left))
		term_cur_left(line, &(pos->l), &(pos->r), cols);
	else if (!term_strcmp(buf->str, key_right))
		term_cur_right(line, &(pos->l), &(pos->r), cols);
	else if (*buf->str == '\x7f' || !term_strcmp(buf->str, key_backspace))
		term_del_char(line, &(pos->l), cols);
	else if (ft_strcmp(buf->str, "\033") && \
			term_strcmp(buf->str, "\n") && term_strcmp(buf->str, "\4"))
		term_write( line, &(pos->l), buf, cols);
}

void	term_line_handler(t_string *buf, t_string *line, int cols)
{
	t_pos	pos;

	// write(1, PROMPT, PROMPT_SIZE);
	// tputs(save_cursor, 1, ft_putchar);
	// tstr_clear(line);

	pos.l = 0;
	pos.r = 0;
	while (term_strcmp(buf->str, "\n") && \
			(term_strcmp(buf->str, "\4") || pos.l))
	{
		clear_str(buf->str, BUF_SIZE);
		buf->len = read(0, buf->str, BUF_SIZE);
		term_keycode_handler(buf, line, cols, &pos);
	}
}

// void	minishell(char *pname, t_list **env)
// {
// 	t_string		*buf;
// 	t_string		*line;
// 	t_hisory		*history;
// 	struct termios	orig;
// 	int				cols;

// 	history = history_init(pname, env);
// 	buf = term_buf_init();
// 	term_set_attr(&orig);
// 	cols = tgetnum("co");
// 	line = tstr_create();
// 	while(strcmp(buf->str, "\4"))
// 	{
// 		term_line_handler(buf, line, cols);
// 		history_add(line->str, &(history->begin));
// 		printf("\nline = |%s|\n", line->str); //parser
// 	}
// 	tstr_free(line);
// 	tstr_free(buf);
// 	write(1, "\n", 1);

// 	history_save(history->fname, history->begin); // in success_exit
// 	history_free(history);
// 	tcsetattr(0, TCSANOW, &orig); //  in success_exit
// }

int main()
{
	t_string *buf;
	struct termios orig;
	t_string *line;
	int cols;

	buf = term_buf_init();
	term_set_attr(&orig);
	cols = tgetnum("co");
	line = tstr_create();
	while(strcmp(buf->str, "\4"))
	{
		write(1, PROMPT, PROMPT_SIZE);
		tputs(save_cursor, 1, ft_putchar);
		tstr_clear(line);
		clear_str(buf->str, BUF_SIZE);
		term_line_handler(buf, line, cols);
		printf("\nline = |%s|\n", line->str);
	}
	tstr_free(line);
	write(1, "\n", 1);
	tcsetattr(0, TCSANOW, &orig);
	//minishell(argv[0],);
	return (0);
}
