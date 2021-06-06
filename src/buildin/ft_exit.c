/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:16:29 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/06 19:14:20 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "exit.h"
#include "utils.h"
#include "ft_term.h"

//argv must be null terminated
void	ft_exit(char **argv)
{
	int			i;
	long long	code;

	printf("%sexit\n", PROMPT);
	if (!argv)
		success_exit(0);
	i = 0;
	while (argv[i] && i < 2)
		i++;
	if (i == 0)
		success_exit(0);
	else if (i > 1)
		printf("exit: too many arguments\n");
	else
	{
		code = ft_atoll(argv[0], &i);
		if (i)
			success_exit(((char)code));
		else
			printf("exit: %s: numeric argument required\n", argv[0]);
	}
}
