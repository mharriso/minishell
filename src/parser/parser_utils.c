/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:34 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/18 17:37:59 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "exit.h"

void	line_init(t_line *line, char *str)
{
	line->data = str;
	line->status = NORMAL;
	line->index = 0;
	line->len = ft_strlen(str) + 1;
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
	new->len = 0;
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
	new->len = 0;
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

void	clear_tokens(t_token **lst, void (*del)(void *))
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

void *ft_realloc(void *ptr, size_t src_size, size_t new_size)
{
	void *new;

	new = NULL;
	if(ptr && src_size < new_size)
	{
		new = malloc(new_size);
		if(!new)
			return (NULL);
		ft_memcpy(new, (const void *)ptr, src_size);
		free(ptr);
	}
	return (new);
}
