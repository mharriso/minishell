#ifndef TSTR_H
# define TSTR_H

# include <stdlib.h>
# include "libft.h"

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	pos;
}				t_string;

int			tstr_init(t_string *string);
t_string	*tstr_create(void);
int			tstr_clear(t_string *str);
void		tstr_free(t_string *str);
int			tstr_resize(t_string *str, size_t len);

#endif
