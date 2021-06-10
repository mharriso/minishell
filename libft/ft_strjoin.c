/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:50:54 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/07 19:49:32 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*s;
	size_t		i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (*s1)
			s[i] = *(s1++);
		else
			s[i] = *(s2++);
		i++;
	}
	s[i] = '\0';
	return (s);
}
