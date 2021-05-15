/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:16:29 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/15 17:33:08 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "exit.h"

void	ft_exit(char **argv)
{
	int			i;
	long long	code;

	printf("exit\n");
	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
		printf("exit: too many arguments\n");
	else
	{
		i = 1; //ft_atoll(argv[0], &code);
		code = 1;
		if (i)
			success_exit(((char)code));
		else
			printf("exit: %s: numeric argument required\n", argv[0]);
	}
}
