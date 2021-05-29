#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

#include <signal.h>

# define RLK_LEFT_ARR     "\033[D"
# define RLK_RIGHT_ARR    "\033[C"
# define RLK_UP_ARR          "\033[A"
# define RLK_DOWN_ARR     "\033[B"

#define BUF_SIZE 8

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

void	tstr_add_size(t_string *str, const char *src, size_t len)
{
	char	*temp;

	if ((len + str->pos) > str->len)
	{
		while ((len + str->pos) > str->len)
			str->len <<= 1;
		temp = str->str;
		str->str = malloc(str->len + 1);
		ft_memcpy(str->str, temp, str->pos + 1);
		free(temp);
	}
	ft_strlcat(str->str, src, len + str->pos + 1);
	str->pos += len;
}

void	tstr_add(t_string *str, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	tstr_add_size(str, src, len);
}

void	tstr_remove(t_string *str)
{
	if (str->pos < 1)
		return ;
	str->pos--;
	str->str[str->pos] = '\0';
}

int	ft_putchar(int c)
{
	int res;
	res = write(1, &c, 1);
	return (0);
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

void	term_del_char(t_string *str, size_t *pos)
{
	if (pos)
	{
		tstr_remove(str);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		(*pos)--;
	}
}

void	term_write(const char *msg, t_string *str, size_t len)
{
	tstr_add_size(str, msg, len);
	write(1, msg, len);
}

void	term_write_history(const char *msg, t_string *str, size_t *pos)
{
	size_t	len;

	len = ft_strlen(msg);
	str->pos = 0;
	term_write(msg, str, len);
	*pos = len;
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

int main()
{
	char buff[BUF_SIZE];
	int len;
	int res;
	size_t pos;
	size_t posr;
	struct termios new;
	struct termios orig;
	char *term_name;
	t_string *line;

	term_name = getenv("TERM");
	if (tgetent(0, term_name) != 1)
		exit(EXIT_FAILURE);
	tcgetattr(0, &orig);
	new = orig;
	new.c_lflag &= ~(ECHO);
	new.c_lflag &= ~(ICANON);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new);

	line = tstr_create();
	while(strcmp(buff, "\4"))
	{
		write(1, "minishell: ", 11);
		tputs(save_cursor, 1, ft_putchar);
		pos = 0;
		posr = 0;
		tstr_clear(line);
		do
		{
			clear_str(buff, BUF_SIZE);
			len = read(0, buff, BUF_SIZE);
			if (!term_strcmp(buff, key_up))
			{
				tputs(restore_cursor, 1, ft_putchar);
				term_write_history("up", line, &pos);
				tputs(clr_eol, 1, ft_putchar);
			}
			else if (!term_strcmp(buff, key_down))
			{
				tputs(restore_cursor, 1, ft_putchar);
				term_write_history("down", line, &pos);
				tputs(clr_eol, 1, ft_putchar);
			}
			else if (!term_strcmp(buff, key_left))
			{
				if (pos)
				{
					tputs(cursor_left, 1, ft_putchar);
					pos--;
					posr++;
				}
			}
			else if (!term_strcmp(buff, key_right))
			{
				if (posr)
				{
					tputs(cursor_right, 1, ft_putchar);
					pos++;
					posr--;
				}
			}
			else if (*buff == '\x7f')
				term_del_char(line, &pos);
			else if (ft_strcmp(buff, "\033"))
			{
				term_write(buff, line, len);
				pos += len;
			}
		} while (term_strcmp(buff, "\n") && term_strcmp(buff, "\4"));
		tstr_remove(line);
		printf("\nline = |%s|\n", line->str);
	}
	tstr_free(line);
	write(1, "\n", 1);
	tcsetattr(0, TCSANOW, &orig);
	return (0);
}
