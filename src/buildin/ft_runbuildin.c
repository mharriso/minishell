/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_runbuildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:27:46 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/10 16:04:21 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"
#include "libft.h"
#include "exit.h"

static char	*ft_absname(char *arg)
{
	char	*name;
	size_t	i;
	size_t	len;

	len = ft_strlen(arg);
	name = malloc(len + 1);
	if (!name)
		error_exit("ft_absname");
	i = 0;
	while (i < len)
	{
		name[i] = ft_tolower(arg[i]);
		i++;
	}
	name[i] = '\0';
	return (name);
}

//argv must be from argv[1]
int	ft_runbuildin(char **argv, t_list **env)
{
	char	*name;
	int		res;

	res = -1;
	name = ft_absname(argv[0]);
	if (!ft_strcmp("cd", name))
		res = ft_cd(argv + 1, env);
	else if (!ft_strcmp("echo", name))
		res = ft_echo(argv + 1);
	else if (!ft_strcmp("env", name))
		res = ft_env(*env);
	else if (!ft_strcmp("exit", name))
		ft_exit(argv + 1);
	else if (!ft_strcmp("export", name))
		res = ft_export(argv + 1, env);
	else if (!ft_strcmp("pwd", name))
		res = ft_pwd();
	else if (!ft_strcmp("unset", name))
		res = ft_unset(argv + 1, env);
	free(name);
	return (res);
}
