#ifndef BUILDIN_H
# define BUILDIN_H

# define PWD_BUFF 256

# include "libft.h"

int		ft_echo(char **argv);
int		ft_pwd(void);
int		ft_cd(char **argv, t_list **env);
int		ft_env(t_list *env);
int		ft_export(char **argv, t_list **env);
void	ft_exit(char **argv);
int		ft_unset(char **argv, t_list **env);
int		ft_runbuildin(char **argv, t_list **env);

#endif
