#ifndef TERM_UTILS_H
# define TERM_UTILS_H

# include "tstr.h"

typedef struct s_pos
{
	size_t	l;
	size_t	r;
	int		cols;
}				t_pos;

int		term_putchar(int c);
void	term_clear_str(char *str, int size);
int		term_strcmp(const char *s1, const char *s2);
void	term_cur_vert(const char *str, t_string *line, size_t *pos);
void	term_cur_left(t_string *str, size_t *pos, size_t *posr, int cols);
void	term_cur_right(t_string *str, size_t *pos, size_t *posr, int cols);
void	term_cur_left_ol(int cols, size_t pos);
void	term_write( t_string *str, size_t *pos, t_string *buff, int cols);
void	term_del_char(t_string *str, size_t *pos, int cols);

#endif
