/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:34 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/06 19:11:48 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "exit.h"

void	line_init(t_line *line, char **str)
{
	line->data = str;
	line->status = NORMAL;
	line->index = 0;
	line->len = ft_strlen(*str) + 1;
}

void	create_new_token(t_token **tokens, int len)
{
	t_token	*new;

	if ((*tokens)->type == EMPTY)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if (!new || !new->data)
		error_exit("malloc error");
	new->type = EMPTY;
	new->len = 0;
	new->next = *tokens;
	new->prev = NULL;
	(*tokens)->prev = new;
	*tokens = new;
}

void	start_tokens(t_token **tokens, int len)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if (!new || !new->data)
		error_exit("malloc error");
	new->type = EMPTY;
	new->len = 0;
	new->next = *tokens;
	new->prev = NULL;
	*tokens = new;
}

int	token_lst_size(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	clear_tokens_next(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if (del)
			del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}

void	clear_tokens_prev(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->prev;
		if (del)
			del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}

t_token	*token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	save_twins(t_token **tokens, t_line *line, char c, int type)
{
	create_new_token(tokens, 2);
	(*tokens)->type = type;
	(*tokens)->data[(*tokens)->len++] = c;
	(*tokens)->data[(*tokens)->len++] = (*(line->data))[++line->index];
	create_new_token(tokens, line->len - line->index);
}

void	save_one(t_token **tokens, t_line *line, char c, int type)
{
	create_new_token(tokens, 1);
	(*tokens)->type = type;
	(*tokens)->data[(*tokens)->len++] = c;
	create_new_token(tokens, line->len - line->index);
}

void	add_symbol(t_token **tokens, char c, int type)
{
	if ((*tokens)->type == ENV)
		type = ENV;
	(*tokens)->type = type;
	(*tokens)->data[(*tokens)->len++] = c;
}

void	*ft_realloc(void *src, size_t src_size, size_t new_size)
{
	void	*new;

	new = NULL;
	if (src && src_size < new_size)
	{
		new = malloc(new_size);
		if (!new)
			error_exit("malloc error");
		ft_memcpy(new, (const void *)src, src_size);
		if (src)
			free(src);
	}
	else
		return (src);
	return (new);
}
