/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:45:30 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/16 17:45:00 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list *new;

	if ((new = (t_list *)malloc(sizeof(t_list))))
	{
		new->data = data;
		new->next = NULL;
	}
	return (new);
}
