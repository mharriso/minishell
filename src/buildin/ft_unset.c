/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 21:23:41 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/13 18:27:37 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "env_func.h"

static int is_equal(char *str, char *env)
{
	while (*env != '=' && *str)
	{
		if (*str != *env)
			return (0);
		str++;
		env++;
	}
	return (1);
}

static int unset(char *name, char ***env)
{
	int		equal;

	while (**env)
	{
		equal = is_equal(name, **env);
		if (equal)
		{
			while (**env)
			{
				**env = *(*env + 1);
				(*env)++;
			}
			return (1);
		}
		(*env)++;
	}
	return (0);
}

static void override_env(char ***env, int size)
{
	int		new_size;
	char	**new_env;
	char	**new_env_begin;

	new_size = env_len(*env) - size;
	new_env = (char**)malloc(sizeof(char*) * (new_size + 1));
	new_env_begin = new_env;
	while (**env)
	{
		*new_env = **env;
		new_env++;
		(*env)++;
	}
	*new_env = NULL;
	free(*env);
	*env = new_env_begin;
}

//argv must be null terminated, env - pointer to **env
void	ft_unset(char **argv, char ***env)
{
	int		is_suit;
	int		unset_count;

	if (!*argv)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	unset_count = 0;
	while (*argv)
	{
		is_suit = env_name_check(*argv);
		if (!is_suit)
			printf("unset: %s: invalid parameter name\n", *argv);
		else
			unset_count += unset(*argv, env);
		argv++;
	}
	if (unset_count)
		override_env(env, unset_count);
}
