/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:38:13 by mharriso          #+#    #+#             */
/*   Updated: 2020/11/06 20:18:14 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t		start;
	size_t		end;

	if (!s || !set)
		return (0);
	start = 0;
	end = ft_strlen(s);
	while (ft_strchr(set, s[start]) && s[start])
		start++;
	if (start == end || end == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s[end]))
		end--;
	return (ft_substr(s, start, end - start + 1));
}
