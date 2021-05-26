/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:57 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/26 20:01:09 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include <string.h> //delete

//static unsigned int g_ret;

void	parse_redirect(t_token **tokens, t_line *line, char c)
{
	if (c == '<')
	{
		create_new_token(tokens, 1);
		(*tokens)->type =  RED_LEFT;
		(*tokens)->data[(*tokens)->len++] = c;
		create_new_token(tokens, line->len);
	}
	else if (c == '>' && (*(line->data))[line->index + 1] == '>')
	{
		create_new_token(tokens, 2);
		(*tokens)->type =  RED_DRIGHT;
		(*tokens)->data[(*tokens)->len++] = c;
		(*tokens)->data[(*tokens)->len++] = (*(line->data))[++line->index];
		create_new_token(tokens, line->len);
	}
	else if (c == '>')
	{
		create_new_token(tokens, 1);
		(*tokens)->type =  RED_RIGHT;
		(*tokens)->data[(*tokens)->len++] = c;
		create_new_token(tokens, line->len);
	}
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
int	check_first_symbol(t_token **tokens, t_line *line, char c)
{
	int res;

	if(c == ' ' || c == '\0' || (c == '\"' && line->status == IN_DQUOTES))
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = '$';
		return (0);
	}
	if(c == '\'' || c == '\"')
		return (0);
	res = ft_isalpha(c) || c == '_';
	line->index++;
	if(c == '?')
	{
		(*tokens)->data[(*tokens)->len++] = '!'; //example
		return (0);
	}
	if(res)
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

void semicolon_handler(t_line *line)
{
	char *tmp;

	line->status = SEMICOLON;
	tmp = ft_strdup(*(line->data) + line->index + 1);
	free(*(line->data));
	*(line->data) = tmp;

}

void	parse_normal(t_token **tokens, t_line *line, t_list **env, char c)
{
	if (c == '\"')
		line->status = IN_DQUOTES;
	else if (c == '\'')
		line->status = IN_QUOTES;
	else if (c == '>' || c == '<')
		parse_redirect(tokens, line, c);
	else if (c == ' ' || c == '\t')
		create_new_token(tokens, line->len);
	else if (c == '|')
	{
		create_new_token(tokens, 1);
		(*tokens)->type = PIPE;
		(*tokens)->data[(*tokens)->len++] = c;
		create_new_token(tokens, line->len);
	}
	else if (c == '$')
		parse_env(tokens, line, env);
	else if (c == ';')
		semicolon_handler(line);
	else if (c == '\\')
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = (*(line->data))[++line->index];
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
}

void	parse_in_dquotes(t_token **tokens, t_line *line, t_list **env, char c)
{
	if (c == '\"')
		line->status = NORMAL;
	else if (c == '$')
		parse_env(tokens, line, env);
	else if (c == '\\')
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = (*(line->data))[++line->index];
	}
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
}

void	parse_in_quotes(t_token **tokens, t_line *line, char c)
{
	if (c == '\'')
		line->status = NORMAL;
	else
	{
		(*tokens)->type = TEXT;
		(*tokens)->data[(*tokens)->len++] = c;
	}
}

t_token	*parse_line(char **str, t_list **env)
{
	t_token		*tokens;
	t_line		line;

	tokens = NULL;
	line_init(&line, str);
	start_tokens(&tokens, line.len);
	while ((*(line.data))[line.index])
	{
		if (line.status == NORMAL)
			parse_normal(&tokens, &line, env, (*(line.data))[line.index]);
		else if (line.status == IN_DQUOTES)
			parse_in_dquotes(&tokens, &line, env, (*(line.data))[line.index]);
		else if (line.status == IN_QUOTES)
			parse_in_quotes(&tokens, &line, (*(line.data))[line.index]);
		if (line.status == SEMICOLON)
			return (tokens);
		line.index++;
	}
	free(*str);
	*str = NULL;
	//printf("g_ret = %d\n", g_ret);
	return (tokens);
}
