/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:09 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/16 14:27:39 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "buildin.h"

void	ft_pwd(void)
{
	char	*p;

	p = getcwd(NULL, PWD_BUFF);
	if (!p)
		write(1, "pwd: error\n", 12);
	else
	{
		write(1, p, PWD_BUFF);
		write(1, "\n", 1);
		free(p);
	}
}
