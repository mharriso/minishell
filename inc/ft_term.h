#ifndef FT_TERM_H
# define FT_TERM_H

# define PROMPT "minishell: "
# define PROMPT_SIZE 11
# define BUF_SIZE 8

# include "libft.h"

int		ft_term(char *pname, t_list **env);
void	term_set_attr();

#endif
