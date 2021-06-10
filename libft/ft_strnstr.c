/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:31:31 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/07 19:54:57 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	if (!little[0])
		return ((char *)big);
	len_little = ft_strlen(little);
	i = 0;
	while (big[i] && i + len_little <= len)
	{
		if (!(ft_strncmp(big + i, little, len_little)))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
