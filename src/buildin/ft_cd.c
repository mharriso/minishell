/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:05 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/17 19:23:42 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "env_func.h"
#include "buildin.h"

void	ft_cd(char **argv, t_list **env)
{
	int		res;
	char	*value;
	char	*new_path;

	res = chdir(argv[0]);
	if (res == -1)
		printf("cd: %s: No such file or directory", argv[0]);
	else
	{
		new_path = getcwd(NULL, PWD_BUFF);
		value = env_getvaluebyname("PWD", *env);
		env_replace("OLDPWD", value, env);
		env_replace("PWD", new_path, env);
	}
}
