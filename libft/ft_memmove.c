/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:56:18 by mharriso          #+#    #+#             */
/*   Updated: 2020/10/31 17:11:14 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if ((const unsigned char *)src < (unsigned char *)dst)
		while (n--)
			((unsigned char *)dst)[n] = ((const unsigned char *)src)[n];
	if ((const unsigned char *)src > (unsigned char *)dst)
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	return (dst);
}
