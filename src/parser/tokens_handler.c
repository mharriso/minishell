#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"
#include "parser.h"
#include "env_func.h"
#include "com_func.h"
#include "red_func.h"
#include "structs.h"


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

// void	create_command_lst(t_token *tokens, t_list **env)
// {

// }

void	tokens_handler(t_token *tokens, t_list **env)
{
	t_list		*commands;
	t_redir		*red;


	while (tokens)
	{
		if(tokens->type == SEMICOLON)
		{
			commands_handler(commands, env);
			ft_lstclear(&commands, com_clear);
		}
		if(tokens->type == PIPE)
		{
			com_create();
		}
		if(tokens->type < PIPE)
		{
			red_create();
		}

		tokens = tokens->prev;
	}

}

