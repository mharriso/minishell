/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:53:05 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/05 17:22:27 by tjuliean         ###   ########.fr       */
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
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		n++;
		i++;
	}
	t = i;
	while (argv[i])
	{
		if (i != t)
			printf(" ");
		printf("%s", argv[i]);
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
