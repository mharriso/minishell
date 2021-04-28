/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:19 by tjuliean          #+#    #+#             */
/*   Updated: 2021/04/17 21:14:27 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_func.h"

int main (int argc, char **argv, char **env)
{
	if (argc == 2)
	{
		ft_cd(argv[1]);
	}
	else if (argc == 3)
	{
		ft_export(argv[1], &env);
		ft_env((const char **)env);
	}
	else
		ft_pwd();
	return (0);
}
