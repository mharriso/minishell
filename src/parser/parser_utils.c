/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:34 by mharriso          #+#    #+#             */
/*   Updated: 2021/05/16 16:27:49 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int		add_new_elem(t_list **lst, char *s)
{
	t_list	*elem;

	elem = NULL;
	if (!(elem = ft_lstnew(s)))
		return (1);
	ft_lstadd_front(lst, elem);
	return (0);
}
