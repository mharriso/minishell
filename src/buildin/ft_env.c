/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:34:48 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/16 14:52:05 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "structs.h"

static void	print_env(void *v)
{
	t_env *env;

	env = (t_env*)v;
	if (env->value)
		printf("%s=%s\n", env->name, env->value);
}

void	ft_env(t_list *env)
{
	ft_lstiter(env, print_env);
}