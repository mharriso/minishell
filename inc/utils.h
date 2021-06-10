#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "parser.h"

long long	ft_atoll(char *str, int *ok);
char		*get_full_path(const char *name, t_list *env);
void		sort_env(char **env);
void		print_error(const char *name, const char *msg);
t_token		*ft_wildcard(const char *wc);

#endif
