/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/30 18:12:34 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include <string.h> //delete

static unsigned int g_ret;

void	parse_redirect(t_token **tokens, t_line *line, char c)
{
	if (c == '<')
		save_one(tokens, line, c, RED_LEFT);
	else if (c == '>' && (*(line->data))[line->index + 1] == '>')
		save_twins(tokens, line, c, RED_DRIGHT);
	else if (c == '>')
		save_one(tokens, line, c, RED_RIGHT);
}

char *get_env_name(t_line *line)
{
	char	*name;
	char	c;
	int		res;
	int		i;

	name = malloc(line->len - line->index + 1);
	if(!name)
		error_exit("malloc error");
	c = (*(line->data))[line->index];
	i = 0;
	while(1)
	{
		res = ft_isalnum(c) || c == '_';
		if(!c || !res)
			break ;
		name[i] = c;
		c = (*(line->data))[++line->index];
		i++;
	}
	line->index--;
	name[i] = '\0';
	return (name);
}

void	save_return_res(t_token **tokens)
{
	char	*str_ret;
	char	*tmp;

	str_ret = ft_itoa(g_ret);
	tmp = ft_strjoin((*tokens)->data, str_ret);
	free((*tokens)->data);
	(*tokens)->data = tmp;
	(*tokens)->len += ft_strlen(str_ret);
	free(str_ret);
}

int	check_first_symbol(t_token **tokens, t_line *line, char c)
{
	int res;

	res = ft_isalpha(c) || c == '_';
	if(c == ' ' || c == '\0' || (c == '\"' && line->status == IN_DQUOTES))
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = '$';
		return (0);
	}
	if(c == '\'' || c == '\"')
		return (0);
	line->index++;
	if(c == '?')
		save_return_res(tokens);
	else if(res)
		return (1);
	return (0);
}

void parse_env(t_token **tokens, t_line *line, t_list **env)
{
	char	*name;
	char	*value;
	int		res;
	char	*tmp;

	(*tokens)->type = TEXT;
	res = check_first_symbol(tokens, line, (*(line->data))[line->index + 1]);
	if(!res)
		return ;
	name = get_env_name(line);
	value = env_getvaluebyname(name, *env);
	free(name);
	//printf("name  = |%s|\nvalue = %s\n", name, value);
	if(!value)
		return ;
	tmp = ft_strjoin((*tokens)->data, value);
	if(!tmp)
		error_exit("malloc error\n");
	free((*tokens)->data);
	(*tokens)->data = tmp;
	(*tokens)->len += ft_strlen(value);
}

void parse_separator(t_token **tokens, t_line *line, char c)
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
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}

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
		if((*(line->data))[line->index + 1] != '\'' && \
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
		add_symbol(tokens, (*(line->data))[++line->index], TEXT);
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


void syntax_error(char *str)
{
	printf("%s: syntax error near unexpected token `%s'\n", PROMPT, str);
	g_ret = 258;
}

void	check_tokens(t_token *last)
{
	t_token	*previous;

	previous = last;
	if(last->type < TEXT)
	{
		syntax_error(last->data);
		return ;
	}
	while ((last = last->prev))
	{
		if(previous->type < TEXT && last->type < TEXT)
		{
			syntax_error(last->data);
			return ;
		}
		if(previous->type < SEMICOLON && last->type == EMPTY)
		{
			syntax_error(previous->data);
			return ;
		}
		previous = last;
	}
}
