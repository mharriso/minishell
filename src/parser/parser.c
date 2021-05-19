/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/18 18:24:59 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include <string.h> //delete


void	finish_redirect_token(t_token **tokens, t_line *line, char c)
{
	if (c != '>' && (*tokens)->type == R_REDIRECT)
		create_new_token(tokens, line->len);
}

void	parse_normal(t_token **tokens, t_line *line, char c)
{
	finish_redirect_token(tokens, line, c);
	if (c == '\"')
	{
		create_new_token(tokens, line->len);
		line->status = IN_DQUOTES;
	}
	else if (c == '\'')
	{
		create_new_token(tokens, line->len);
		line->status = IN_QUOTES;
	}
	else if (c == '>' && (*tokens)->type == R_REDIRECT)
	{
		(*tokens)->type = DR_REDIRECT;
		(*tokens)->data[(*tokens)->len++] = c;
		create_new_token(tokens, line->len);
	}
	else if (c == '>')
	{
		create_new_token(tokens, line->len);
		(*tokens)->type = R_REDIRECT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
	else if (c == '<')
	{
		create_new_token(tokens, line->len);
		(*tokens)->type = L_REDIRECT;
		(*tokens)->data[(*tokens)->len++] = c;
		create_new_token(tokens, line->len);
	}
	else if (c == ' ' || c == '\t')
		create_new_token(tokens, line->len);
	else if (c == '|')
	{
		create_new_token(tokens, line->len);
		(*tokens)->type = PIPE;
		(*tokens)->data[(*tokens)->len++] = c;
		create_new_token(tokens, line->len);
	}
	//else if (c == '$')
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
}

void	parse_in_quotes(t_token **tokens, t_line *line, char c)
{
	if (c == '\'')
	{
		create_new_token(tokens, line->len);
		line->status = NORMAL;
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
}

void	parse_in_dquotes(t_token **tokens, t_line *line, char c)
{
	if (c == '\"')
	{
		create_new_token(tokens, line->len);
		line->status = NORMAL;
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
}

char *type(int type) //delete
{
	if(type == EMPTY)
		return strdup("EMPTY");
	else if(type == TEXT)
		return strdup("TEXT");
	else if(type == R_REDIRECT)
		return strdup("R_REDIRECT");
	else if(type == DR_REDIRECT)
		return strdup("DR_REDIRECT");
	else if(type == L_REDIRECT)
		return strdup("L_REDIRECT");
	else if(type == PIPE)
		return strdup("PIPE");
	else
		return strdup("ERROR TYPE");
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
		printf("%-11s:  %s\n", type(tmp->type), tmp->data); //delete
		if (!(arr[size] = malloc(tmp->len + 1)))
			error_exit("malloc error");
		ft_memcpy(arr[size], tmp->data, tmp->len);
		arr[size][tmp->len] = '\0';
		tmp = tmp->next;
	}
	return (arr);
}

char	**parser(char *str)
{
	t_token		*tokens;
	t_line		line;
	char		**tokens_arr;

	tokens = NULL;
	line_init(&line, str);
	start_tokens(&tokens, line.len);
	while (line.data[line.index])
	{
		if (line.status == NORMAL)
			parse_normal(&tokens, &line, line.data[line.index]);
		else if (line.status == IN_QUOTES)
			parse_in_quotes(&tokens, &line, line.data[line.index]);
		else if (line.status == IN_DQUOTES)
			parse_in_dquotes(&tokens, &line, line.data[line.index]);
		line.index++;
	}
	int size = token_lst_size(tokens);
	printf("list size = %d\n\n", size);
	tokens_arr = create_array(&tokens, size);
	clear_tokens(&tokens, free);
	return (tokens_arr);
}
