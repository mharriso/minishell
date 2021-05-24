/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:08:45 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/18 17:19:20 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#define NORMAL 1
#define IN_QUOTES 2
#define IN_DQUOTES 3
#define EMPTY 0
#define TEXT 4
#define R_REDIRECT 5
#define L_REDIRECT 6
#define DR_REDIRECT 7
#define PIPE 8

typedef struct s_line
{
	char	*data;
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

char	**parser(char *line);
void	create_new_token(t_token **tokens, int len);
void	start_tokens(t_token **tokens, int len);
int		token_lst_size(t_token *lst);
void	line_init(t_line *line, char *str);
void	*ft_realloc(void *ptr, size_t src_size, size_t new_size);
void	clear_tokens(t_token **lst, void (*del)(void *));


#endif
