/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:28:36 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/05 19:58:37 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "exit.h"
#include "env_func.h"
#include "buildin.h"
#include "structs.h"
#include "utils.h"

static void	export(const char *name, const char *value, t_list **env)
{
	t_list	*node;
	t_env	*content;

	content = (t_env *)malloc(sizeof(t_env));
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

static void	show_env(t_list *env)
{
	char	**temp;

	temp = env_listtoarr(env);
	sort_env(temp);
	free(temp);
}

static void	handle_env(char *arg, int res, t_list **env, int *ret)
{
	t_env	new_e;

	if (res)
	{
		new_e.value = env_getvalue(arg);
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
		*ret = 1;
	}
	new_e.name = env_getname(arg);
	res = env_name_check(new_e.name);
}

//argv must be null terminated, env - pointer to *env
int	ft_export(char **argv, t_list **env)
{
	int		res;
	int		ret;

	ret = 0;
	if (!*argv)
		show_env(*env);
	while (*argv)
	{
		res = is_env(*argv);
		if (!res)
		{
			argv++;
			continue ;
		}
		handle_env(*argv, res, env, &ret);
		argv++;
	}
	return (ret);
}
