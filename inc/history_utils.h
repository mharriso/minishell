#ifndef HISTORY_UTILS_H
# define HISTORY_UTILS_H

# include "libft.h"

char	*history_get_fname(char term_num, const char *pname);
char	*history_get_shlvl(t_list **env);

#endif
