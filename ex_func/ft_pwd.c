/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:17:09 by tjuliean          #+#    #+#             */
/*   Updated: 2021/04/17 21:00:25 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ex_func.h"
#include "exit.h"

void	ft_pwd(void)
{
	char	*p;

	p = getcwd(NULL, PWD_BUFF);
	if (!p)
		error_exit("ft_pwd");
	write(1, p, PWD_BUFF);
	write(1, "\n", 1);
	free(p);
}
