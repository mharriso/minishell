#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"
# include "dlist.h"

# define HISTORY_FNAME "history/history_term"

typedef struct s_history
{
	t_dlist	*cur;
	t_dlist	*begin;
	char	*fname;
}				t_hisory;

t_hisory	*history_init(const char *pname, t_list **env);
char		*history_up_arrow(t_dlist **cur_history);
char		*history_down_arrow(t_dlist **cur_history);
void		history_add(const char *content, t_dlist **history);
void		history_save(const char *fname, t_dlist *history);
void		history_free(t_hisory *history);

#endif
