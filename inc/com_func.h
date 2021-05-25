#ifndef COM_FUNC_H
# define COM_FUNC_H

#include "libft.h"
#include "structs.h"

char		**com_getcom(t_list *list);
t_redir		*com_getredir(t_list *list);
int			com_getptype(t_list *list);
t_fork		*com_getinfo(t_list *list);
void		com_clear(void *command);
t_command	*com_create(char **commands, t_redir *red, int pipe_type);
int			commands_handler(t_list *com_list, t_list **env);

#endif
