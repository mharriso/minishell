/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:07:17 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/10 23:58:56 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exit.h"
#include "env_func.h"

static	char	*get_env_name(char	**src)
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

static	t_str	*create_env_str(char *src, t_list **env)
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
	str->len += part_len;
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
