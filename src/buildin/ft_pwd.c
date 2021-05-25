/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:09 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/25 15:00:54 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "buildin.h"

int	ft_pwd(void)
{
	char	*p;

	p = getcwd(NULL, PWD_BUFF);
	if (!p)
	{
		printf("pwd: error\n");
		return (1);
	}
	else
	{
		printf("%s\n", p);
		free(p);
	}
	return (0);
}
