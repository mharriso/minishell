#include "parser.h"
#include <stdio.h>
#include "ft_term.h"
#include "com_func.h"
#include "exit.h"

static unsigned int	g_ret;

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

	end = *tokens;
	while (*tokens)
	{
		tokens_handler(tokens, env, &end);
		commands = create_com_lst(tokens, env);
		if (commands)
		{
			g_ret = commands_handler(commands, env);
			ft_lstclear(&commands, com_clear);
		}
	}
	clear_tokens_prev(&end, free);
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
