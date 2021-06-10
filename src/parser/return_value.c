#include "parser.h"
#include <stdio.h>
#include "ft_term.h"
#include "com_func.h"
#include "exit.h"


static unsigned int	g_ret;

char	*type(int type) //delete
{
	if (type == EMPTY)
		return ft_strdup("EMPTY");
	else if (type == TEXT)
		return ft_strdup("TEXT");
	else if (type ==  RED_RIGHT)
		return ft_strdup("RED_RIGHT");
	else if (type ==  RED_DRIGHT)
		return ft_strdup("RED_DRIGHT");
	else if (type ==  RED_LEFT)
		return ft_strdup("RED_LEFT");
	else if (type == PIPE)
		return ft_strdup("PIPE");
	else if (type == SEMICOLON)
		return ft_strdup("SEMICOLON");
	else if (type == OR)
		return ft_strdup("OR");
	else if (type == AND)
		return ft_strdup("AND");
	else if (type & ENV)
		return ft_strdup("ENV");
	else if (type & WILDCARD)
		return ft_strdup("WILDCARD");
	else
		return ft_strdup("ERROR TYPE");
}

void	print_tokens(t_token *lst)
{
	printf("   TOKENS\n");
	while (lst)
	{
		printf("%-11s:  %s\n", type(lst->type), lst->data);
		lst = lst->prev;
	}
	printf("\n\n");
}

void	syntax_error(char *str)
{
	printf("%s: syntax error near unexpected token `%s'\n", PROMPT, str);
	g_ret = 258;
}

t_token	*parser(char *line)
{
	t_token	*tokens;

	tokens = parse_line(&line);
	check_last_token(&tokens);
	tokens = token_last(tokens);
	if (!check_tokens(tokens))
		clear_tokens_prev(&tokens, free);
	return (tokens);
}

void	tokens_to_commands(t_token **tokens, t_list **env)
{
	t_list		*commands;
	t_token		*end;
	t_token		*end2;


	end = *tokens;
	end2 = *tokens;

	while (*tokens)
	{
		print_tokens(end);
		tokens_handler(*tokens, env);
		commands = create_com_lst(tokens, env);
		if (commands)
		{
			g_ret = commands_handler(commands, env);
			ft_lstclear(&commands, com_clear);
		}
	}
	clear_tokens_prev(&end2, free);
}

void	add_env_value(t_str *str, char **src, t_list **env)
{
	char	*value;
	size_t	value_len;

	value = NULL;
	if (**src == '?')
	{
		(*src)++;
		value = ft_itoa(g_ret);
		if (!value)
			error_exit("malloc error");
	}
	else if (ft_isalpha(**src) || **src == '_')
		value = get_env_value(src, env);
	if (value)
	{
		value_len = ft_strlen(value);
		str->data = ft_realloc(str->data, str->len, str->len + value_len + 1);
		ft_memcpy(str->data + str->len, value, value_len);
		str->len += value_len;
		free(value);

	}
}

int	run_parser(char *line, t_list **env)
{
	t_token	*tokens;

	tokens = parser(line);
	if (tokens)
		tokens_to_commands(&tokens, env);
	return (g_ret);
}
