/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:55:06 by mharriso          #+#    #+#             */
/*   Updated: 2021/06/07 20:48:52 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 128

static void	free_cache(char **cache)
{
	free(*cache);
	*cache = NULL;
}

static	int	save_next_line(char *buffer, char **line, char **cache)
{
	char	*new_line;
	char	*tmp;

	if (!buffer)
		return (0);
	new_line = ft_strchr(buffer, '\n');
	if (new_line)
		*new_line = '\0';
	tmp = ft_strjoin(*line, buffer);
	if (!tmp)
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	if (new_line && *(new_line + 1) != '\0')
	{
		tmp = ft_strdup(new_line + 1);
		if (!tmp)
			return (-1);
	}
	free(*cache);
	*cache = tmp;
	if (new_line)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*cache = NULL;
	char		buffer[BUFFER_SIZE + 1];
	int			res;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	*line = ft_calloc(1, 1);
	if (!*line)
		return (-1);
	res = save_next_line(cache, line, &cache);
	if (res == 1)
		return (res);
	res = read(fd, buffer, BUFFER_SIZE);
	while (res > 0)
	{
		buffer[res] = '\0';
		res = save_next_line(buffer, line, &cache);
		if (res != 0)
			break ;
		res = read(fd, buffer, BUFFER_SIZE);
	}
	if (res == -1 || res == 0)
		free_cache(&cache);
	return (res);
}
