#ifndef FT_TERM_H
# define FT_TERM_H

# include "libft.h"

# define PROMPT "minishell: "
# define PROMPT_SIZE 11
# define BUF_SIZE 8

int		ft_term(char *pname, t_list **env);
void	term_set_attr(void);
void	restor_params(void);

#endif
