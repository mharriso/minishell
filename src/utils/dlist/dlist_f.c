#include "dlist.h"
#include <stdlib.h>

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*node;

	node = (t_dlist *)malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prew = NULL;
	return (node);
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_dlstsize(t_dlist *lst)
{
	int	res;

	if (!lst)
		return (0);
	res = 1;
	while (lst->next)
	{
		res++;
		lst = lst->next;
	}
	return (res);
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *newl)
{
	t_dlist	*last;

	if (!newl || !lst)
		return ;
	if (*lst)
	{
		last = ft_dlstlast(*lst);
		last->next = newl;
		newl->prew = last;
	}
	else
		*lst = newl;
}

void	ft_dlstadd_front(t_dlist **lst, t_dlist *newl)
{
	if (!lst || !newl)
		return ;
	if (*lst)
		(*lst)->prew = newl;
	newl->next = *lst;
	*lst = newl;
}
