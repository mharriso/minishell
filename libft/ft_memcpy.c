/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:56:07 by mharriso          #+#    #+#             */
/*   Updated: 2020/10/31 17:04:47 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	size_t			i;

	i = 0;
	if (dest == source)
		return (dest);
	while (i < count)
	{
		((unsigned char*)dest)[i] = ((const unsigned char*)source)[i];
		i++;
	}
	return (dest);
}
