/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:08:45 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/20 17:46:49 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#define NORMAL 1
#define IN_QUOTES 2
#define IN_DQUOTES 3
#define EMPTY 0
#define TEXT 4
#define RED_RIGHT 5
#define RED_LEFT 6
#define RED_DRIGHT 7
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

char	**parser(char *str, t_list **env);
void	create_new_token(t_token **tokens, int len);
void	start_tokens(t_token **tokens, int len);
int		token_lst_size(t_token *lst);
void	clear_tokens(t_token **lst, void (*del)(void *));
void	line_init(t_line *line, char *str);
void	*ft_realloc(void *ptr, size_t src_size, size_t new_size);



#endif
