/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:31:31 by mharriso          #+#    #+#             */
/*   Updated: 2020/11/07 04:44:55 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t len_little;

	len_little = ft_strlen(little);
	i = 0;
	while (big[i] && i + len_little <= len)
	{
		if (!(ft_strncmp(big + i, little, len_little)))
			return ((char *)big + i);
		i++;
	}
	return ((!little[0]) ? (char *)big : NULL);
}
