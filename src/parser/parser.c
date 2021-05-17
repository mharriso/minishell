/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/17 18:08:27 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#define NORMAL 1
#define IN_QUOTES 2
#define IN_DQUOTES 3

typedef struct s_parse
{
	char	*line;
	int		status;
	int		index;
	int		len;
}				t_parse;

typedef struct	s_token
{
	char			*data;
	int				type;
	int				index;
	struct s_token	*next;
}				t_token;

void	create_new_token(t_token **tokens, int len)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if(!new || !new->data)
		error_exit("malloc error");
	new->type = 0;
	new->index = 0;

	new->next = *tokens;
	*tokens = new;
}

int	lstsize(t_token *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	parse_normal(t_token **tokens, t_parse *parse, char c)
{
	if (c == '\"')
		parse->status = IN_DQUOTES;
	else if (c == '\'')
		parse->status = IN_QUOTES;
	else if (c == ' ' || c == '\t')
	{
		printf("Normal\n");
		create_new_token(tokens, parse->len);
	}
	else
		(*tokens)->data[(*tokens)->index++] = c;
}

// void	parse_in_quotes(t_token *tokens, t_parse *parse, char c)
// {
// 	if (c == '\'')
// 		parse->status = NORMAL;
// }

// void	parse_in_dquotes(t_token *tokens, t_parse *parse, char c)
// {
// 	if (c == '\"')
// 		parse->status = NORMAL;
// }
void	parse_init(t_parse *parse, char *line)
{
	parse->line = line;
	parse->status = NORMAL;
	parse->index = 0;
	parse->len = ft_strlen(line) + 1;
}


char		**create_array(t_token **head, int size)
{
	char	**arr;
	t_token	*tmp;

	tmp = *head;
	if (!(arr = malloc((size + 1) * sizeof(char *))))
		error_exit("malloc error");
	arr[size] = NULL;
	while (tmp)
	{
		size--;
		if (!(arr[size] = malloc(tmp->index + 1)))
			error_exit("malloc error");
		ft_memcpy(arr[size], tmp->data, tmp->index);
		arr[size][tmp->index] = '\0';
		tmp = tmp->next;
	}
	return (arr);
}

char	**parser(char *line)
{
	t_token		*tokens;
	t_parse		parse;

	tokens = NULL;
	parse_init(&parse, line);
	create_new_token(&tokens, parse.len);
	while (parse.line[parse.index])
	{
		if (parse.status == NORMAL)
			parse_normal(&tokens, &parse, parse.line[parse.index]);
		// else if (parse.status == IN_QUOTES)
		// 	parse_in_quotes(tokens, &parse, parse.line[parse.index]);
		// else if (parse.status == IN_DQUOTES)
		// 	parse_in_dquotes(tokens, &parse, parse.line[parse.index]);
		parse.index++;
	}
	int size = lstsize(tokens);
	printf("list size = %d\n", size);
	return (create_array(&tokens, size));
}
