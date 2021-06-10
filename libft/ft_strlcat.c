/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:51:15 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/07 19:49:43 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (dst[len] && len < size)
		len++;
	while (src[i] && len + i + 1 < size)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < size)
		dst[len + i] = '\0';
	while (src[i])
		i++;
	return (i + len);
}
