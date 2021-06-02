#ifndef DLIST_H
# define DLIST_H

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prew;
}				t_dlist;

t_dlist	*ft_dlstnew(void *content);
t_dlist	*ft_dlstlast(t_dlist *lst);
int		ft_dlstsize(t_dlist *lst);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *newl);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *newl);
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
void	ft_dlstdelone(t_dlist *lst, void (*del)(void*));
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));

#endif
