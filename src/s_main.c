/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:32:03 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/17 19:42:16 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "structs.h"
#include "env_func.h"
#include "buildin.h"

static char	**fill_arg(int argc, char **argv)
{
	char	**arg;

	arg = malloc(sizeof(char*) * argc);
	for (int i = 1; i < argc; i++)
		arg[i - 1] = argv[i];
	arg[argc - 1] = NULL;

	return (arg);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*lenv;
	char	**arg;

	lenv = env_create(env);

	// if (argc == 2)
	// {
	// 	arg = malloc(sizeof(char*) * 2);
	// 	arg[0] = argv[1];
	// 	arg[1] = NULL;
	// 	ft_unset(arg, &lenv);
	// 	ft_env(lenv);
	// }
	arg = fill_arg(argc, argv);
	ft_unset(arg, &lenv);

	// char *a;
	// a = malloc(3);
	// a[0] = '.';
	// a[1] = '.';
	// a[2] = '\0';

	// ft_cd(&a ,&lenv);

	ft_env(lenv);
	//ft_pwd();

	//free(a);
	free(arg);

	ft_lstclear(&lenv, env_clear);
	return (0);
}
