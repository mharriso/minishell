/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:58:21 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/21 16:45:09 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "exit.h"

#include <stdio.h>

char	*e_name(t_list *env)
{
	return ((t_env*)env->content)->name;
}

char	*e_value(t_list *env)
{
	return ((t_env*)env->content)->value;
}

char	*env_getname(char *str)
{
	char	*begin;
	char	*name;

	begin = str;
	while (*str != '=' && *str != '\0')
		str++;
	if (*str == '\0')
		return (NULL);
	*str = '\0';
	name = ft_strdup(begin);
	if (!name)
		error_exit("env_getname");
	*str = '=';
	return (name);
}

char	*env_getvalue(char *str)
{
	char	*value;

	while (*str != '=' && *str != '\0')
		str++;
	if (*str == '\0')
		return (NULL);
	*str = '\0';
	value = ft_strdup(str + 1);
	if (!value)
		error_exit("env_getnvalue");
	*str = '=';
	return (value);
}

char	*env_getvaluebyname(const char *name, t_list *env)
{
	char	*env_name;
	int		res;

	while (env)
	{
		env_name = e_name(env);
		res = ft_strcmp(name, env_name);
		if (!res)
			return (e_value(env));
		env = env->next;
	}
	return (NULL);
}

int		env_name_check(char *str)
{
	int		res;

	res = ft_isalpha(*str) || *str == '_';
	while (*str != '\0' && res)
	{
		res = ft_isalnum(*str) || *str == '_';
		str++;
	}
	return (res);
}

static void	env_freecont(t_env *env)
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
int	env_replace(const char *name, const char *value, t_list **env)
{
	t_list	*temp;
	int		res;

	temp = *env;
	while (temp)
	{
		res = ft_strcmp(name, ((t_env*)temp->content)->name);
		if (!res)
		{
			env_freecont((t_env*)temp->content);
			((t_env*)temp->content)->name = ft_strdup(name);
			((t_env*)temp->content)->value = ft_strdup(value);
			if (!((t_env*)temp->content)->name || !((t_env*)temp->content)->value)
				error_exit("env_replace");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

t_list	*env_create(char **env)
{
	t_list	*list;
	t_list	*node;
	t_env	*content;
	int		res;

	list = NULL;
	while (*env)
	{
		content = (t_env*)malloc(sizeof(t_env));
		content->name = env_getname(*env);
		res = ft_strcmp("OLDPWD", content->name);
		if (res)
			content->value = env_getvalue(*env);
		else
			content->value = NULL;
		node = ft_lstnew(content);
		ft_lstadd_back(&list, node);
		env++;
	}
	return (list);
}

static char	*str_env(char *name, char *value)
{
	size_t	i;
	char	*str;

	i = ft_strlen(name);
	i += ft_strlen(value);
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (*name)
	{
		str[i] = *name;
		name++;
		i++;
	}
	str[i++] = '=';
	while (*value)
	{
		str[i] = *value;
		value++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**env_listtoarr(t_list *env)
{
	char	**new_env;
	char	*value;
	char	*name;
	int	i;

	i = ft_lstsize(env);
	new_env = (char**)malloc(sizeof(char*) * (i + 1));
	if (!new_env)
		error_exit("env_listtoarr\n");
	i = 0;
	while (env)
	{
		name = e_name(env);
		value = e_value(env);
		if (value)
			new_env[i] = str_env(name, value);
		else
			new_env[i] = ft_strdup(name);
		if (!new_env[i])
			error_exit("env_listtoarr\n");
		i++;
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

static int	lstsize_wo_v(t_list *lst)
{
	int		i;
	char	*value;

	i = 0;
	while (lst)
	{
		value = e_value(lst);
		if (value)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**env_listtoarr_to_new(t_list *env)
{
	char	**new_env;
	char	*value;
	char	*name;
	int		i;

	i = lstsize_wo_v(env);
	new_env = (char**)malloc(sizeof(char*) * (i + 1));
	if (!new_env)
		error_exit("env_listtoarr\n");
	i = 0;
	while (env)
	{
		name = e_name(env);
		value = e_value(env);
		if (value)
		{
			new_env[i] = str_env(name, value);
			if (!new_env[i])
				error_exit("env_listtoarr\n");
			i++;
		}
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
