/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:05 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/26 16:33:15 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "libft.h"
#include "env_func.h"
#include "buildin.h"

int	ft_cd(char **argv, t_list **env)
{
	int			res;
	char		*value;
	char		*new_path;
	struct stat	buf;

	if (!argv[0])
	{
		new_path = env_getvaluebyname("HOME", *env);
		res = chdir(new_path);
	}
	else
		res = chdir(argv[0]);
	if (res == -1)
	{
		res = stat(argv[0], &buf);
		if (res)
			printf("cd: %s: No such file or directory", argv[0]);
		else
			printf("cd: %s: Not a directory", argv[0]);
		return (1);
	}
	else
	{
		new_path = getcwd(NULL, PWD_BUFF);
		value = env_getvaluebyname("PWD", *env);
		env_replace("OLDPWD", value, env);
		env_replace("PWD", new_path, env);
	}
	return (0);
}
