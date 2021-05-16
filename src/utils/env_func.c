/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:58:21 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/16 15:17:27 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "structs.h"

#include <stdio.h>

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

	res = ft_isalpha(*str) || *str == '_';
	while (str++ && res)
		res = ft_isalnum(*str) || *str == '_';
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

//return -1 if env hasn't name
int		env_index_byname(const char *name, const char **env)
{
	int		i;
	int		res;
	char	*env_name;

	i = 0;
	while (env[i])
	{
		env_name = env_getname((char*)env[i]);
		res = ft_strcmp(name, env_name);
		free(env_name);
		if (!res)
			return (i);
		i++;
	}
	return (-1);
}

//char	*env_getval_byname(const char *name, const char **env)
//{

//}



void	env_freecont(t_env *env)
{

	free(env->name);
	if (env->value)
		free(env->value);
}

void	env_clear(void *v)
{
	env_freecont((t_env*)v);
	free(v);
}

//return 1 if success
int		env_replace(const char *str, t_list **env)
{
	char	*name;
	t_list	*temp;
	int		res;

	name = env_getname((char*)str);
	temp = *env;
	while (temp)
	{
		res = ft_strcmp(name, ((t_env*)temp->content)->name);
		if (!res)
		{
			env_freecont((t_env*)temp->content);
			((t_env*)temp->content)->name = name;
			((t_env*)temp->content)->value = env_getvalue((char*)str);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

t_list	*env_create(char **env)
{
	t_list	*list;
	t_list	*node;
	t_env	*content;

	list = NULL;
	while (*env)
	{
		content = (t_env*)malloc(sizeof(t_env));
		content->name = env_getname(*env);
		content->value = env_getvalue(*env);
		node = ft_lstnew(content);
		ft_lstadd_back(&list, node);
		env++;
	}
	return (list);
}
