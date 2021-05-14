/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:55:06 by mharriso          #+#    #+#             */
/*   Updated: 2021/03/02 04:18:18 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 128

static	int	save_next_line(char *buffer, char **line, char **cache)
{
	char	*new_line;
	char	*tmp;

	if (!buffer)
		return (0);
	if ((new_line = ft_strchr(buffer, '\n')))
		*new_line = '\0';
	if (!(tmp = ft_strjoin(*line, buffer)))
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	if (new_line && *(new_line + 1) != '\0')
		if (!(tmp = ft_strdup(new_line + 1)))
			return (-1);
	free(*cache);
	*cache = tmp;
	return ((new_line) ? 1 : 0);
}

int			get_next_line(int fd, char **line)
{
	static char	*cache = NULL;
	char		buffer[BUFFER_SIZE + 1];
	int			res;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || !(*line = (char *)malloc(1)))
		return (-1);
	**line = '\0';
	if ((res = save_next_line(cache, line, &cache)) == 1)
		return (res);
	while ((res = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[res] = '\0';
		res = save_next_line(buffer, line, &cache);
		if (res != 0)
			break ;
	}
	if (res == -1 || res == 0)
	{
		if (res == -1)
			free(*line);
		free(cache);
		cache = NULL;
	}
	return (res);
}
