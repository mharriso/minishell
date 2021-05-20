/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:32:03 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/18 16:58:25 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "structs.h"
#include "env_func.h"
#include "buildin.h"

// static char	**fill_arg(int argc, char **argv)
// {
// 	char	**arg;

// 	arg = malloc(sizeof(char*) * argc);
// 	for (int i = 1; i < argc; i++)
// 		arg[i - 1] = argv[i];
// 	arg[argc - 1] = NULL;

// 	return (arg);
// }

int	main(int argc, char **argv, char **env)
{
	t_list	*lenv;

	lenv = env_create(env);

	if (argc > 1)
	{
		ft_runbuildin(argv + 1, &lenv);
	}

	ft_lstclear(&lenv, env_clear);
	return (0);
}
