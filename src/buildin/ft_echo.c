/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:53:05 by tjuliean          #+#    #+#             */
/*   Updated: 2021/07/24 19:45:58 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_echo(char **argv)
{
	int		n;
	int		i;
	int		t;

	n = 0;
	i = 0;
	while (argv[i] && !ft_strcmp(argv[i], "-n"))
	{
		n++;
		i++;
	}
	t = i;
	while (argv[i])
	{
		if (i != t)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
