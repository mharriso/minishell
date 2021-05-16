#ifndef EX_FUNC_H
# define EX_FUNC_H

# define PWD_BUFF 128

#include "libft.h"

void	ft_pwd(void);
void	ft_cd(const char *path);
void	ft_env(t_list *env);
void	ft_export(char **argv, char ***env);
void	ft_exit(void);
void	ft_unset(char **argv, char ***env);

#endif
