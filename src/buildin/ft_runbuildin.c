/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_runbuildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:27:46 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/06 20:08:24 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"
#include "libft.h"

static char	*ft_absname(char *arg)
{
	char	*name;
	size_t	i;
	size_t	len;

	len = ft_strlen(arg);
	name = malloc(len + 1);
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

	name = ft_absname(argv[0]);
	if (!ft_strcmp("cd", name))
		return (ft_cd(argv + 1, env));
	else if (!ft_strcmp("echo", name))
		return (ft_echo(argv + 1));
	else if (!ft_strcmp("env", name))
		return (ft_env(*env));
	else if (!ft_strcmp("exit", name))
		ft_exit(argv + 1);
	else if (!ft_strcmp("export", name))
		return (ft_export(argv + 1, env));
	else if (!ft_strcmp("pwd", name))
		return (ft_pwd());
	else if (!ft_strcmp("unset", name))
		return (ft_unset(argv + 1, env));
	return (-1);
}
