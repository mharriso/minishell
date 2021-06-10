/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:38:00 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/07 19:55:08 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = 0;
	len = ft_strlen(str) + 1;
	while (len--)
		if (str[len] == (char)c)
			return ((char *)str + len);
	return (NULL);
}
