/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:05 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/15 17:25:21 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_cd(const char *path, char ***env)
{
	int	res;

	res = chdir(path);
	if (res == -1)
		perror("cd"); // to strerror
	else
	{
		env = NULL;
	}
}
