/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:28:36 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/16 16:14:50 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "exit.h"
#include "env_func.h"
#include "buildin.h"

static void	print_env(char **env)
{
	while (*env)
	{
		printf("declare -x  %s\n", *env);
		env++;
	}

}

static char	**sort_env(char **env)
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
	return (env);
}

static char	**fill_new_env(int len, char **env, char *new_str)
{
	int		i;
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		error_exit("ft_export/fill_new_env");
	i = 0;
	len--;
	while (i < len)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i++] = new_str;
	new_env[i++] = env[len];
	new_env[i] = NULL;
	return (new_env);
}

static void	export(char *str, char ***env)
{
	int		len;
	char	*new_str;

	len = 0;
	while ((*env)[len])
		len++;
	new_str = ft_strdup(str);
	if (!new_str)
		error_exit("ft_export");
	*env = fill_new_env(len, *env, new_str);
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

//argv must be null terminated, env - pointer to **env
void		ft_export(char **argv, char ***env)
{
	int		res;
	char	*name;
	char	**temp;

	if (!*argv)
	{
		temp = sort_env(*env);
		print_env(temp);
	}
	while (*argv)
	{
		res = is_env(*argv);
		if (!res)
			continue ;
		name = env_getname(*argv);
		res = env_name_check(name);
		if (res)
		{
			res = env_replace(*argv, env);
			if (!res)
				export(*argv, env);
		}
		else
			printf("export: not an identifier: %s\n", name);
		free(name);
		argv++;
	}
}
