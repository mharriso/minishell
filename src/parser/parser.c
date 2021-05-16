/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/16 18:19:20 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#define NORMAL 1
#define IN_QUOTES 2
#define IN_DQUOTES 3

typedef struct s_parse
{
	char	*line;
	int		status;
	int		token_type;
	int		index;
	int		len;
}				t_parse;

void	parse_normal(t_list *tokens, t_parse *parse, char c)
{
	if(c == '\"')
		parse->status = IN_DQUOTES;
	else if(c == '\'')
		parse->status = IN_QUOTES;
}

void	parse_in_quotes(t_list *tokens, t_parse *parse, char c)
{
	if(c == '\'')
		parse->status = NORMAL;
}

void	parse_in_dquotes(t_list *tokens, t_parse *parse, char c)
{
	if(c == '\"')
		parse->status = NORMAL;
}

char	**parser(char *line)
{
	t_list		*tokens;
	t_parse		parse;

	parse.line = line;
	parse.status = NORMAL;
	tokens = NULL;
	while (parse.line[parse.index])
	{
		if (parse.status == NORMAL)
			parse_normal(tokens, &parse, parse.line[parse.index]);
		else if (parse.status == IN_QUOTES)
			parse_in_quotes(tokens, &parse, parse.line[parse.index]);
		else if (parse.status == IN_DQUOTES)
			parse_in_dquotes(tokens, &parse, parse.line[parse.index]);
		parse.index++;
	}
	return (0);
}
