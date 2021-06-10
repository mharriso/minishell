#include "parser.h"
#include "exit.h"
#include "env_func.h"
#include "utils.h"

char	*get_env_name(char	**src)
{
	char	*name;
	int		i;

	i = 0;
	while (ft_isalnum((*src)[i]) || (*src)[i] == '_')
		i++;
	name = malloc(i + 1);
	if (!name)
		error_exit("malloc error");
	i = 0;
	while (ft_isalnum(**src) || **src == '_')
	{
		name[i] = **src;
		(*src)++;
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_env_value(char **src, t_list **env)
{
	char	*name;
	char	*value;

	name = get_env_name(src);
	value = env_getvaluebyname(name, *env);
	free(name);
	if (value)
	{
		value = ft_strdup(value);
		if (!value)
			error_exit("get_env_value");
	}
	return (value);
}

t_str	*create_env_str(char *src, t_list **env)
{
	t_str	*str;
	char	*dollar;
	int		part_len;

	dollar = ft_strchr(src, '$');
	str = malloc(sizeof(t_str));
	str->data = ft_strdup("");
	str->len = 0;
	while (dollar)
	{
		part_len = dollar - src;
		str->data = ft_realloc(str->data, str->len, str->len + part_len + 1);
		ft_memcpy(str->data + str->len, src, part_len);
		str->len += part_len;
		src = dollar + 1;
		add_env_value(str, &src, env);
		dollar = ft_strchr(src, '$');
	}
	part_len = ft_strlen(src);
	str->data = ft_realloc(str->data, str->len, str->len + part_len + 1);
	ft_memcpy(str->data + str->len, src, part_len + 1);
	return (str);
}

void	env_handler(t_token *tokens, t_list **env)
{
	t_str	*env_str;

	env_str = create_env_str(tokens->data, env);
	free(tokens->data);
	tokens->data = env_str->data;
	tokens->len = env_str->len;
	free(env_str);
}

static void	free_tok(t_token *tokens)
{
	free(tokens->data);
	free(tokens);
}

static t_token	*wildcard_handler(t_token *tokens, t_token **ret)
{
	t_token	*wc_end;
	t_token	*wc_start;
	t_token	*tok_end;
	t_token	*tok_start;

	wc_end = ft_wildcard(tokens->data);
	if (wc_end)
	{
		tok_start = tokens->next;
		tok_end = tokens->prev;
		free_tok(tokens);
		wc_start = token_last(wc_end);
		if (ret)
			*ret = wc_start;
		if (tok_start)
			tok_start->prev = wc_start;
		wc_start->next = tok_start;
		wc_end->prev = tok_end;
		if (tok_end)
			tok_end->next = wc_end;
		if (tok_end)
			return (tok_end);
		return (wc_end);
	}
	return (tokens);
}

void	tokens_handler(t_token **cur, t_list **env, t_token **end)
{
	t_token	*tokens;

	tokens = *cur;
	if (tokens->type & WILDCARD)
	{
		if (tokens->type & ENV)
			env_handler(tokens, env);
		tokens = wildcard_handler(tokens, cur);
		*end = *cur;
		tokens = tokens->prev;
	}
	while (tokens && (tokens->type != SEMICOLON))
	{
		if (tokens->type & ENV)
			env_handler(tokens, env);
		if (tokens->type & WILDCARD)
			tokens = wildcard_handler(tokens, NULL);
		tokens = tokens->prev;
	}
}
