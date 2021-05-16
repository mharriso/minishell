/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:32:03 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/16 14:54:15 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "structs.h"
#include "env_func.h"
#include "buildin.h"

int	main(int argc, char **argv, char **env)
{
	// v to test v
	int c;
	char **v;
	c = argc;
	v = argv;
	// ^ to test ^

	t_list	*lenv;

	lenv = env_create(env);

	ft_env(lenv);

	ft_lstclear(&lenv, env_clear);
	return (0);
}
