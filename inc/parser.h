/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:08:45 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/26 19:08:53 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#define NORMAL 1
#define IN_QUOTES 2
#define IN_DQUOTES 3
#define SEMICOLON 9
#define EMPTY 0
#define TEXT 4
#define RED_RIGHT 5
#define RED_LEFT 6
#define RED_DRIGHT 7
#define PIPE 8

#define BLUE "\033[34;1m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define ARROW "\U000027A1"
#define SHELL "\U0001F41A"
#define CROSS "\U0000274E"
#define DOLLAR GREEN"$"RESET
#define DIAMOND "\U0001F538"
#define PROMPT SHELL" "DIAMOND BLUE"-msh-"RESET DIAMOND" "
typedef struct s_line
{
	char	**data;
	int		status;
	int		index;
	int		len;
}				t_line;

typedef struct	s_token
{
	char			*data;
	int				type;
	int				len;
	struct s_token	*next;
}				t_token;

t_token	*parse_line(char **str, t_list **env);
void	create_new_token(t_token **tokens, int len);
void	start_tokens(t_token **tokens, int len);
int		token_lst_size(t_token *lst);
void	clear_tokens(t_token **lst, void (*del)(void *));
void	line_init(t_line *line, char **str);
void	*ft_realloc(void *ptr, size_t src_size, size_t new_size);



#endif
