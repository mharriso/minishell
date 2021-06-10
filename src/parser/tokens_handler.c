#include "parser.h"
#include "exit.h"
#include "env_func.h"

#include <stdio.h> // delete

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
	printf("name = %s value = %s\n", name, value);
	return (value);
}

t_str	*create_env_str(char *src, t_list **env)
{
	t_str	*str;
	char	*dollar;
	int		part_len;

	dollar = ft_strchr(src, '$');
	str = malloc(sizeof(str));
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
}

// static char	*type(int type) //delete
// {
// 	if (type == EMPTY)
// 		return ft_strdup("EMPTY");
// 	else if (type == TEXT)
// 		return ft_strdup("TEXT");
// 	else if (type == PIPE)
// 		return ft_strdup("PIPE");
// 	else if (type == SEMICOLON)
// 		return ft_strdup("SEMICOLON");
// 	else if (type == OR)
// 		return ft_strdup("OR");
// 	else if (type == AND)
// 		return ft_strdup("AND");
// 	else if (type & ENV)
// 		return ft_strdup("ENV");
// 	else if (type & WILDCARD)
// 		return ft_strdup("WILDCARD");
// 	else
// 		return ft_strdup("ERROR TYPE");
// }

// static void	print_tokens(t_token *lst)
// {
// 	printf("   TOKENS\n");
// 	while (lst)
// 	{
// 		printf("%-11s:  %s\n", type(lst->type), lst->data);
// 		lst = lst->prev;
// 	}
// 	printf("\n\n");
// }

t_token *example()
{
	t_token *wildcard;

	wildcard = NULL;
	start_tokens(&wildcard, 100);
	for(int i = 0; i < 10; i++)
	{
		create_new_token(&wildcard, 2);
		wildcard->data[0] = i + '0';
		wildcard->type = TEXT;
		wildcard->len = 2;
	}
	return (wildcard);
}

// void	wildcard_handler(t_token *tokens)
// {
// 	t_token *wildcard;
// 	//t_token *wildcard_first;

// 	wildcard = example();

// 	printf("OK\n");
// }

void	tokens_handler(t_token *tokens, t_list **env)
{
	while (tokens && (tokens->type != SEMICOLON))
	{
		if (tokens->type & ENV)
			env_handler(tokens, env);
		// if (tokens->type & WILDCARD)
		// 	wildcard_handler(tokens);
		tokens = tokens->prev;
	}
}
