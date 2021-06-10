/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:19:57 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/07 20:06:28 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

// Content - a node with which to delete,
// Size - size in byte to cpm content, del - func to free node
int	ft_lstremove(t_list **list, void *content, size_t size, void (*del)(void*))
{
	t_list	*temp;
	t_list	*prev;
	int		res;

	if (!list || !*list || !del)
		return (0);
	temp = *list;
	prev = NULL;
	while (temp)
	{
		res = ft_memcmp(content, temp->content, size);
		if (!res)
		{
			if (prev)
				prev->next = temp->next;
			else
				*list = temp->next;
			ft_lstdelone(temp, del);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
