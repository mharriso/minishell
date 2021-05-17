/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 21:23:41 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/17 19:46:49 by tjuliean         ###   ########.fr       */
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
void	ft_unset(char **argv, t_list **env)
{
	int		is_suit;
	int		res;

	t_list *t;
	t = *env;
	if (!*argv)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (*argv)
	{
		is_suit = env_name_check(*argv);
		if (!is_suit)
			printf("unset: %s: invalid parameter name\n", *argv);
		else
			res = remove_env(*argv, env);
		argv++;
	}
}
