/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 21:23:41 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/25 15:06:35 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "env_func.h"
#include "libft.h"

int remove_env(char *name, t_list **env)
{
	int		equal;
	t_list	*temp;
	t_list	*prev;

	temp = *env;
	prev = NULL;
	while (temp)
	{
		equal = ft_strcmp(name, e_name(temp));
		if (!equal)
		{
			if (prev)
				prev->next = temp->next;
			else
				*env = temp->next;
			ft_lstdelone(temp, env_clear);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

//argv must be null terminated, env - pointer to *env
int	ft_unset(char **argv, t_list **env)
{
	int		is_suit;
	int		res;
	int		ret;

	ret = 0;
	if (!*argv)
	{
		printf("unset: not enough arguments\n");
		ret = 1;
	}
	while (*argv)
	{
		is_suit = env_name_check(*argv);
		if (!is_suit)
		{
			printf("unset: %s: invalid parameter name\n", *argv);
			ret = 1;
		}
		else
			res = remove_env(*argv, env);
		argv++;
	}
	return (ret);
}
