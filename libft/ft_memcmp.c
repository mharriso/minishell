/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:55:23 by mharriso          #+#    #+#             */
/*   Updated: 2020/10/31 21:13:11 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	size_t		i;
	int			res;

	i = 0;
	res = 0;
	while (i < count)
	{
		res = ((unsigned char *)buf1)[i] - ((unsigned char *)buf2)[i];
		if (res != 0)
			return (res);
		i++;
	}
	return (0);
}
