#ifndef FORK_H
# define FORK_H

# include "structs.h"

void	do_redirect(t_redir *red);
void	exec_external(t_list *com_list, t_list **env);
void	do_pipe(t_list *com_list, t_list **env);

#endif
