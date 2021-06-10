/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:49:39 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/07 21:05:13 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(char const *s, char c)
{
	size_t		count;
	int			i;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] != c && s[i + 1] == c)
			count++;
		i++;
	}
	if (s[i] != c && s[0])
		count++;
	return (count);
}

static	size_t	get_word_len(const char *s, char c)
{
	char		*len;

	len = ft_strchr(s, c);
	if (len != NULL)
		return (len - s);
	return (ft_strlen(s));
}

static	char	**free_words(char **array)
{
	size_t		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	size_t		len;
	size_t		word_len;
	size_t		i;
	size_t		j;

	len = count_words(s, c);
	res = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < len)
	{
		while (s[i] == c)
			i++;
		word_len = get_word_len(s + i, c);
		res[j] = ft_calloc((word_len + 1), sizeof(char));
		if (!res[j])
			return (free_words(res));
		res[j] = ft_memcpy(res[j], s + i, word_len);
		i += word_len;
	}
	return (res);
}
