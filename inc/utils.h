#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

long long	ft_atoll(char *str, int *ok);
char		*get_full_path(const char *name, t_list *env);
void		sort_env(char **env);
void		print_error(const char *name, const char *msg);

#endif
