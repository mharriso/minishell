#include "parser.h"
#include "utils.h"
#include "exit.h"
#include "env_func.h"

static void	free_tok(t_token *tokens)
{
	free(tokens->data);
	free(tokens);
}

static t_token	*wildcard_handler(t_token *tokens, t_token **ret)
{
	t_token	*wc_end;
	t_token	*wc_start;
	t_token	*tok_end;
	t_token	*tok_start;

	wc_end = ft_wildcard(tokens->data);
	if (wc_end)
	{
		tok_start = tokens->next;
		tok_end = tokens->prev;
		free_tok(tokens);
		wc_start = token_last(wc_end);
		if (ret)
			*ret = wc_start;
		if (tok_start)
			tok_start->prev = wc_start;
		wc_start->next = tok_start;
		wc_end->prev = tok_end;
		if (tok_end)
			tok_end->next = wc_end;
		if (tok_end)
			return (tok_end);
		return (wc_end);
	}
	return (tokens);
}

void	tokens_handler(t_token **cur, t_list **env, t_token **end)
{
	t_token	*tokens;

	tokens = *cur;
	if (tokens->type & WILDCARD)
	{
		if (tokens->type & ENV)
			env_handler(tokens, env);
		tokens = wildcard_handler(tokens, cur);
		*end = *cur;
		tokens = tokens->prev;
	}
	while (tokens && (tokens->type != SEMICOLON))
	{
		if (tokens->type & ENV)
			env_handler(tokens, env);
		if (tokens->type & WILDCARD)
			tokens = wildcard_handler(tokens, NULL);
		tokens = tokens->prev;
	}
}
