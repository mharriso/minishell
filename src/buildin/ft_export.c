/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:28:36 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/17 19:39:16 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "exit.h"
#include "env_func.h"
#include "buildin.h"
#include "structs.h"

static void	print_env(char **env)
{
	while (*env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
}

static void	sort_env(char **env)
{
	int		i;
	int		flag;
	int		res;
	char	*temp;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (env[i] && env[i + 1])
		{
			res = ft_strcmp(env[i], env[i + 1]);
			if (res > 0)
			{
				flag = 1;
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
	}
	print_env(env);
}

static void	export(char *name, char *value, t_list **env)
{
	t_list	*node;
	t_env	*content;

	content = (t_env*)malloc(sizeof(t_env));
	if (!content)
		error_exit("ft_export");
	content->name = ft_strdup(name);
	content->value = ft_strdup(value);
	node = ft_lstnew(content);
	if (!node)
		error_exit("ft_export");
	ft_lstadd_back(env, node);
}

static int	is_env(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

//argv must be null terminated, env - pointer to *env
void	ft_export(char **argv, t_list **env)
{
	int		res;
	t_env	new_e;
	char	**temp;

	if (!*argv)
	{
		temp = env_listtoarr(*env);
		sort_env(temp);
		free(temp);
	}
	while (*argv)
	{
		res = is_env(*argv);
		if (!res)
		{
			argv++;
			continue ;
		}
		new_e.name = env_getname(*argv);
		res = env_name_check(new_e.name);
		if (res)
		{
			new_e.value = env_getvalue(*argv);
			res = env_replace(new_e.name, new_e.value, env);
			if (!res)
				export(new_e.name, new_e.value, env);
			free(new_e.name);
			if (new_e.value)
				free(new_e.value);
		}
		else
		{
			printf("export: not an identifier: %s\n", new_e.name);
			free(new_e.name);
		}
		argv++;
	}
}
