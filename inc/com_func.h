#ifndef COM_FUNC_H
# define COM_FUNC_H

#include "libft.h"
#include "structs.h"

char	**com_getcom(t_list *list);
t_redir	*com_getredir(t_list *list);
int		com_getptype(t_list *list);
t_fork	*com_getinfo(t_list *list);

#endif
