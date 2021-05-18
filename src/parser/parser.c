/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/18 14:40:00 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include <string.h> //delete

void	finish_redirect(t_token **tokens, t_parse *parse, char c)
{
	if (c != '>' && (*tokens)->type == R_REDIRECT)
		create_new_token(tokens, parse->len);
}

void	parse_normal(t_token **tokens, t_parse *parse, char c)
{
	finish_redirect(tokens, parse, c);
	if (c == '\"')
		parse->status = IN_DQUOTES;
	else if (c == '\'')
		parse->status = IN_QUOTES;
	else if (c == '>' && (*tokens)->type == R_REDIRECT)
	{
		(*tokens)->type = DR_REDIRECT;
		(*tokens)->data[(*tokens)->index++] = c;
		create_new_token(tokens, parse->len);
	}
	else if (c == '>')
	{
		create_new_token(tokens, parse->len);
		(*tokens)->type = R_REDIRECT;
		(*tokens)->data[(*tokens)->index++] = c;
	}
	else if (c == '<')
	{
		create_new_token(tokens, parse->len);
		(*tokens)->type = L_REDIRECT;
		(*tokens)->data[(*tokens)->index++] = c;
		create_new_token(tokens, parse->len);
	}
	else if (c == ' ' || c == '\t')
		create_new_token(tokens, parse->len);
	else if (c == '|')
	{
		create_new_token(tokens, parse->len);
		(*tokens)->type = PIPE;
		(*tokens)->data[(*tokens)->index++] = c;
		create_new_token(tokens, parse->len);
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->index++] = c;
	}
}

void	parse_in_quotes(t_token **tokens, t_parse *parse, char c)
{
	if (c == '\'')
	{
		create_new_token(tokens, parse->len);
		parse->status = NORMAL;
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->index++] = c;
	}
}

void	parse_in_dquotes(t_token **tokens, t_parse *parse, char c)
{
	if (c == '\"')
	{
		create_new_token(tokens, parse->len);
		parse->status = NORMAL;
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->index++] = c;
	}
}

char *type(int type)
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
		printf("%-11s:  %s\n", type(tmp->type), tmp->data);
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
	start_tokens(&tokens, parse.len);
	while (parse.line[parse.index])
	{
		if (parse.status == NORMAL)
			parse_normal(&tokens, &parse, parse.line[parse.index]);
		else if (parse.status == IN_QUOTES)
			parse_in_quotes(&tokens, &parse, parse.line[parse.index]);
		else if (parse.status == IN_DQUOTES)
			parse_in_dquotes(&tokens, &parse, parse.line[parse.index]);
		parse.index++;
	}
	int size = token_lst_size(tokens);
	printf("list size = %d\n\n", size);
	return (create_array(&tokens, size));
}
