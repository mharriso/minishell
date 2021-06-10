#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "exit.h"

void	clear_tokens_next(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if (del)
			del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}

void	clear_tokens_prev(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->prev;
		if (del)
			del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}

t_token	*token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	start_tokens(t_token **tokens, int len)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if (!new || !new->data)
		error_exit("malloc error");
	new->type = EMPTY;
	new->len = 0;
	new->next = *tokens;
	new->prev = NULL;
	*tokens = new;
}

void	create_new_token(t_token **tokens, int len)
{
	t_token	*new;

	if ((*tokens)->type == EMPTY)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_calloc(len + 1, 1);
	if (!new || !new->data)
		error_exit("malloc error");
	new->type = EMPTY;
	new->len = 0;
	new->next = *tokens;
	new->prev = NULL;
	(*tokens)->prev = new;
	*tokens = new;
}
