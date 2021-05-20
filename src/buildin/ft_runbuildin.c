/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_runbuildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:27:46 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/18 16:56:12 by tjuliean         ###   ########.fr       */
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
void	ft_runbuildin(char **argv, t_list **env)
{
	int		res;
	char	*name;

	name = ft_absname(argv[0]);
	res = ft_strcmp("cd", name);
	if (!res)
		ft_cd(argv + 1, env);
	res = ft_strcmp("echo", name);
	if (!res)
		ft_echo(argv + 1);
	res = ft_strcmp("env", name);
	if (!res)
		ft_env(*env);
	res = ft_strcmp("exit", name);
	if (!res)
		ft_exit(argv + 1);
	res = ft_strcmp("export", name);
	if (!res)
		ft_export(argv + 1, env);
	res = ft_strcmp("pwd", name);
	if (!res)
		ft_pwd();
	res = ft_strcmp("unset", name);
	if (!res)
		ft_unset(argv + 1, env);
}
