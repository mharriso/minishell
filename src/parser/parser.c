/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/06 19:09:26 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include "com_func.h"
#include "red_func.h"
#include "structs.h"

void	parse_redirect(t_token **tokens, t_line *line, char c)
{
	if (c == '<')
		save_one(tokens, line, c, RED_LEFT);
	else if (c == '>' && (*(line->data))[line->index + 1] == '>')
		save_twins(tokens, line, c, RED_DRIGHT);
	else if (c == '>')
		save_one(tokens, line, c, RED_RIGHT);
}

void	parse_separator(t_token **tokens, t_line *line, char c)
{
	if (c == '|' && (*(line->data))[line->index + 1] == '|')
		save_twins(tokens, line, c, OR);
	else if (c == '|')
		save_one(tokens, line, c, PIPE);
	else if (c == '&' && (*(line->data))[line->index + 1] == '&')
		save_twins(tokens, line, c, AND);
	else if (c == ';')
		save_one(tokens, line, c, SEMICOLON);
	else if (c == '&')
		add_symbol(tokens, c, TEXT);
}

void	parse_normal(t_token **tokens, t_line *line, char c)
{
	if (c == '\"')
		line->status = IN_DQUOTES;
	else if (c == '\'')
		line->status = IN_QUOTES;
	else if (c == '>' || c == '<')
		parse_redirect(tokens, line, c);
	else if (c == ' ' || c == '\t')
		create_new_token(tokens, line->len);
	else if (c == ';' || c == '|' || c == '&')
		parse_separator(tokens, line, c);
	else if (c == '\\')
		add_symbol(tokens, (*(line->data))[++line->index], TEXT);
	else if (c == '$')
	{
		if ((*(line->data))[line->index + 1] != '\'' && \
			(*(line->data))[line->index + 1] != '\"')
			add_symbol(tokens, c, ENV);
	}
	else
		add_symbol(tokens, c, TEXT);
}

void	parse_in_dquotes(t_token **tokens, t_line *line, char c)
{
	if (c == '\"')
		line->status = NORMAL;
	else if (c == '$')
		add_symbol(tokens, c, ENV);
	else if (c == '\\')
	{
		if ((*(line->data))[line->index + 1] == '\"' ||
			(*(line->data))[line->index + 1] == '\\')
			add_symbol(tokens, (*(line->data))[++line->index], TEXT);
		else
			add_symbol(tokens, c, TEXT);
	}
	else
		add_symbol(tokens, c, TEXT);
}

void	parse_in_quotes(t_token **tokens, t_line *line, char c)
{
	if (c == '\'')
		line->status = NORMAL;
	else
		add_symbol(tokens, c, TEXT);
}

t_token	*parse_line(char **str)
{
	t_token		*tokens;
	t_line		line;

	tokens = NULL;
	line_init(&line, str);
	start_tokens(&tokens, line.len);
	while ((*(line.data))[line.index])
	{
		if (line.status == NORMAL)
			parse_normal(&tokens, &line, (*(line.data))[line.index]);
		else if (line.status == IN_DQUOTES)
			parse_in_dquotes(&tokens, &line, (*(line.data))[line.index]);
		else if (line.status == IN_QUOTES)
			parse_in_quotes(&tokens, &line, (*(line.data))[line.index]);
		line.index++;
	}
	free(*str);
	*str = NULL;
	return (tokens);
}
