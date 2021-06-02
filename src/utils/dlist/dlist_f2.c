#include "dlist.h"
#include <stdlib.h>

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_dlstdelone(t_dlist *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*temp;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_dlstdelone(temp, del);
	}
	lst = NULL;
}
