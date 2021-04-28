/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:28:36 by tjuliean          #+#    #+#             */
/*   Updated: 2021/04/24 19:03:37 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftlib.h"
#include "exit.h"

static void sort_env(char **env)
{
	int		i;
	int		j;

	i = 0;
	

}

static void	print_sorted_env(char **env)
{

}

static char	**fill_new_env(int len, char **env, char *new_str)
{
	int		i;
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		error_exit("ft_export/fill_new_env");
	i = 0;
	len--;
	while (i < len)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i++] = new_str;
	new_env[i++] = env[len];
	new_env[i] = NULL;
	return (new_env);
}

void		ft_export(const char *str, char ***env)
{
	int		len;
	int		i;
	char	*new_str;

	if (!str)
		print_sorted_env(*env);
	//TODO check str
	len = 0;
	while ((*env)[len])
		len++;
	new_str = ft_strdup(str);
	if (!new_str)
		error_exit("ft_export");
	*env = fill_new_env(len, *env, new_str);
}
