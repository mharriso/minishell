#include <stdio.h>
#include "env_func.h"
#include "structs.h"
#include "ft_term.h"
#include "parser.h"
#include "exit.h"
#include "env_func.h"

static	int	check_neighbors(t_token *previous, t_token *cur)
{
	if (previous->type <= RED_DRIGHT && (cur->type & ~(TEXT | ENV)))
	{
		syntax_error(previous->data);
		return (0);
	}
	if (previous->type <= SEMICOLON && cur->type == SEMICOLON)
	{
		syntax_error(previous->data);
		return (0);
	}
	return (1);
}

int	check_tokens(t_token *cur)
{
	t_token	*previous;

	if (!cur)
		return (1);
	previous = cur;
	if (cur->type == SEMICOLON || cur->type == PIPE)
	{
		syntax_error(cur->data);
		return (0);
	}
	cur = cur->prev;
	while (cur)
	{
		if (!check_neighbors(previous, cur))
			return (0);
		previous = cur;
		cur = cur->prev;
	}
	if (previous->type <= PIPE)
	{
		syntax_error(previous->data);
		return (0);
	}
	return (1);
}

void	check_last_token(t_token **tokens)
{
	if (*tokens && (*tokens)->type == EMPTY)
	{
		if ((*tokens)->next)
		{
			tokens = &(*tokens)->next;
			clear_tokens_prev(&((*tokens)->prev), free);
		}
		else
			clear_tokens_prev(tokens, free);
	}
}

char	*create_str(t_token *tokens)
{
	char	*str;

	str = malloc(tokens->len + 1);
	if (!str)
		error_exit("malloc error");
	ft_memcpy(str, tokens->data, tokens->len + 1);
	return (str);
}
