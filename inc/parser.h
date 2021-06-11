#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

# define NORMAL 1
# define IN_QUOTES 2
# define IN_DQUOTES 3

# define EMPTY 0
# define PIPE 4
# define OR 5
# define AND 6
# define SEMICOLON 7
# define TEXT 8
# define ENV 16
# define WILDCARD 32
# define WORD 56

# define BLUE "\033[34;1m"
# define YELLOW  "\033[33m"
# define GREEN   "\033[32m"
# define RESET   "\033[0m"
# define ARROW "\U000027A1"
# define SHELL "\U0001F41A"
# define CROSS "\U0000274E"
# define DIAMOND "\U0001F538"
//#define PROMPT SHELL" "DIAMOND BLUE"-msh-"RESET DIAMOND" "

# include "libft.h"
typedef struct s_line
{
	char	**data;
	int		status;
	int		index;
	int		len;
}				t_line;

typedef struct s_token
{
	char			*data;
	int				type;
	int				len;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_str
{
	char		*data;
	size_t		len;
}				t_str;

t_token	*parse_line(char **str);
void	create_new_token(t_token **tokens, int len);
void	start_tokens(t_token **tokens, int len);
int		token_lst_size(t_token *lst);
void	clear_tokens_next(t_token **lst, void (*del)(void *));
void	clear_tokens_prev(t_token **lst, void (*del)(void *));
void	line_init(t_line *line, char **str);
void	*ft_realloc(void *src, size_t src_size, size_t new_size);
int		check_tokens(t_token *last);
t_token	*token_last(t_token *lst);
void	save_twins(t_token **tokens, t_line *line, char c, int type);
void	save_one(t_token **tokens, t_line *line, char c, int type);
void	add_symbol(t_token **tokens, char c, int type);
void	tokens_handler(t_token **cur, t_list **env, t_token **end);
void	env_handler(t_token *tokens, t_list **env);
int		run_parser(char *line, t_list	**env);
void	syntax_error(char *str);
void	check_last_token(t_token **tokens);
void	add_env_value(t_str *str, char **src, t_list **env);
char	*get_env_value(char **src, t_list **env);
t_list	*create_com_lst(t_token **tokens, t_list **env);
t_list	*create_com_lst(t_token **tokens, t_list **env);
char	*create_str(t_token *tokens);

#endif
