/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:34 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/17 19:47:58 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "exit.h"

void	parse_init(t_parse *parse, char *line)
{
	parse->line = line;
	parse->status = NORMAL;
	parse->index = 0;
	parse->len = ft_strlen(line) + 1;
}

void	create_new_token(t_token **tokens, int len)
{
	t_token *new;

	if((*tokens)->type == EMPTY)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if(!new || !new->data)
		error_exit("malloc error");
	new->type = EMPTY;
	new->index = 0;
	new->next = *tokens;
	*tokens = new;
}

void	start_tokens(t_token **tokens, int len)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if(!new || !new->data)
		error_exit("malloc error");
	new->type = EMPTY;
	new->index = 0;
	new->next = *tokens;
	*tokens = new;
}

int	token_lst_size(t_token *lst)
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
