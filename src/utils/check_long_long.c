/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_long_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:04:25 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/10 18:07:25 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	check_limit(char *str, int sign)
{
	char	*ll_int;

	if (sign == -1)
		ll_int = ft_strdup("9223372036854775808");
	else
		ll_int = ft_strdup("9223372036854775807");
	while (*str)
	{
		if (*str > *ll_int)
			return (0);
		str++;
		ll_int++;
	}
	return (1);
}

static int	check_num(char *str, int sign)
{
	int		i;

	i = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) || i > 18)
			return (0);
		i++;
	}
	if (i == 19)
		return (check_limit(str, sign));
	return (1);
}

//ok = 1 if success, ok = 0 if fail
long long	ft_atoll(char *str, int *ok)
{
	long long	number;
	int			sign;

	sign = 1;
	*ok = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (!check_num(str, sign))
	{
		*ok = 0;
		return (0);
	}
	number = 0;
	while (*str)
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return (sign * number);
}
