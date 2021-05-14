/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:41:20 by mharriso          #+#    #+#             */
/*   Updated: 2021/03/30 18:55:01 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(char const *s, char *set)
{
	size_t		count;
	int			i;

	i = 0;
	count = 0;
	while (s[i] && s[i + 1])
	{
		if (!(ft_strchr(set, s[i])) && ft_strchr(set, s[i + 1]))
			count++;
		i++;
	}
	count += (!(ft_strchr(set, s[i])) && s[0]) ? 1 : 0;
	return (count);
}

static	size_t	get_word_len(const char *s, char *set)
{
	int i;

	i = 0;
	while (s[i] && !(ft_strchr(set, s[i])))
		i++;
	return (i);
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

char			**ft_split_set(char const *s, char *set, size_t *len)
{
	char		**res;
	size_t		word_len;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	*len = count_words(s, set);
	if (!(res = (char**)ft_calloc((*len + 1), sizeof(char*))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < *len)
	{
		while (ft_strchr(set, s[i]))
			i++;
		word_len = get_word_len(s + i, set);
		if (!(res[j] = ft_calloc((word_len + 1), sizeof(char))))
			return (free_words(res));
		res[j] = ft_memcpy(res[j], s + i, word_len);
		i += word_len;
	}
	return (res);
}
