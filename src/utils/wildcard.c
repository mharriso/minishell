#include "parser.h"
#include "buildin.h"
#include "libft.h"
#include "exit.h"
#include <dirent.h>
#include <stdlib.h>

static void	tok_add(t_token **tokens, char *data)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new)
		new->data = ft_strdup(data);
	if (!new || !new->data)
		error_exit("tok_add");
	new->type = TEXT;
	new->len = ft_strlen(data);
	new->next = *tokens;
	new->prev = NULL;
	if (*tokens)
		(*tokens)->prev = new;
	*tokens = new;
}

static int	wc_check(const char *wc, const char *str)
{
	int	res;

	res = 0;
	while (*wc == *str && *wc)
	{
		wc++;
		str++;
	}
	if (!*wc && !*str)
		res++;
	else if (*wc == '*')
	{
		wc++;
		while (*str)
		{
			if (*wc == *str)
				res += wc_check(wc, str);
			str++;
		}
		res += wc_check(wc, str);
	}
	return (res);
}

static void	find_files(const char *wc, DIR *dp, t_token **tk)
{
	struct dirent	*ep;
	int				res;

	ep = readdir(dp);
	while (ep)
	{
		if (*(ep->d_name) != '.')
		{
			res = wc_check(wc, ep->d_name);
			if (res)
				tok_add(tk, ep->d_name);
		}
		ep = readdir(dp);
	}
}

t_token	*ft_wildcard(const char *wc)
{
	DIR		*dp;
	char	*p;
	t_token	*tk;

	p = getcwd(NULL, PWD_BUFF);
	tk = NULL;
	if (p)
	{
		dp = opendir(p);
		if (dp != NULL)
		{
			find_files(wc, dp, &tk);
			closedir(dp);
		}
		free(p);
	}
	return (tk);
}
