/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:34 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/10 00:19:22 by mharriso         ###   ########.fr       */
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
	if ((*tokens)->type & WORD)
		type |= (*tokens)->type;
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
