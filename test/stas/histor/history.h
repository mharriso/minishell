#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"
# include "dlist.h"

# define HISTORY_FNAME "history/history_term"

typedef struct s_history
{
	t_dlist	*cur;
	t_list	*begin;
	char	*fname;
}				t_hisory;

char		*history_get_fname(char term_num, const char *pname);
char		*history_get_shlvl(t_list **env);
t_hisory	*history_init(char *pname, t_list **env);
char		*history_up_arrow(t_dlist **cur_history);
char		*history_down_arrow(t_dlist **cur_history);
void		history_add(char *content, t_dlist **history);
void		history_save(char *fname, t_dlist *history);

#endif
