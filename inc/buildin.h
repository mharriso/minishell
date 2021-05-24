#ifndef EX_FUNC_H
# define EX_FUNC_H

# define PWD_BUFF 256

#include "libft.h"

void	ft_echo(char **argv);
void	ft_pwd(void);
void	ft_cd(char **argv, t_list **env);
void	ft_env(t_list *env);
void	ft_export(char **argv, t_list **env);
void	ft_exit(char **argv);
void	ft_unset(char **argv, t_list **env);
int		ft_runbuildin(char **argv, t_list **env);

#endif
