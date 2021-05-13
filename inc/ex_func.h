#ifndef EX_FUNC_H
# define EX_FUNC_H

# define PWD_BUFF 128

void	ft_pwd(void);
void	ft_cd(const char *path);
void	ft_env(const char **env);
void	ft_export(const char *str, char ***env);
void	ft_exit(void);
void	ft_unset(char **argv, char ***env);

#endif
