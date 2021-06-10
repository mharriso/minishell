#include <stdio.h>
#include "env_func.h"
#include "structs.h"
#include "ft_term.h"
#include "parser.h"
#include "exit.h"
#include "env_func.h"

int	check_tokens(t_token *last)
{
	t_token	*previous;

	if(!last)
		return (1);
	previous = last;
	if(last->type == SEMICOLON || last->type == PIPE)
	{
		syntax_error(last->data);
		return 0;
	}
	while ((last = last->prev))
	{
		// if(previous->type <= RED_DRIGHT && last->type & (TEXT | ENV))
		// {
		// 	syntax_error(previous->data);
		// 	return 0;
		// }
		if(previous->type <= SEMICOLON && last->type == SEMICOLON)
		{
			syntax_error(previous->data);
			return 0;
		}
		previous = last;
	}
	if(previous->type <= PIPE)
	{
		syntax_error(previous->data);
		return 0;
	}
	return 1;
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
