/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:58:21 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/13 18:41:55 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftlib.h"

char	*env_getname(char *str)
{
	char	*begin;
	char	*name;

	begin = str;
	while (*str != '=')
		str++;
	*str = '\0';
	name = ft_strdup(begin);
	*str = '=';
	return (name);
}

char	*env_getvalue(char *str)
{
	char	*value;

	while (*str != '=')
		str++;
	*str = '\0';
	value = ft_strdup(str + 1);
	*str = '=';
	return (value);
}

int		env_name_check(char *str)
{
	int		res;

	res = ft_isalpha(*str);
	while (str++ && res)
		res = ft_isalnum(*str);
	return (res);
}

int		env_len(char **env)
{
	int len;

	len = 0;
	while (*env)
	{
		len++;
		env++;
	}
	return (len);
}

char	**env_dup(char **env)
{
	int		len;
	char	**new_env;
	char	**begin;

	len = env_len(env);
	new_env = (char**)malloc(sizeof(char*) * (len + 1));
	begin = new_env;
	while (*env)
	{
		*new_env = ft_strdup(*env);
		env++;
		new_env++;
	}
	*new_env = NULL;
	return (begin);
}
