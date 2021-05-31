#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "env_func.h"

#include "exit.h"
#include "env_func.h"
#include <string.h> //delete

#define BLUE "\033[34;1m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define ARROW "\U000027A1"
#define SHELL "\U0001F41A"
#define CROSS "\U0000274E"
#define DOLLAR GREEN"$"RESET
#define DIAMOND "\U0001F538"

static unsigned int g_ret;

void syntax_error(char *str)
{
	printf("%s: syntax error near unexpected token `%s'\n", PROMPT, str);
	g_ret = 258;
}

void	check_tokens(t_token *last)
{
	t_token	*previous;

	previous = last;
	if(last->type == SEMICOLON || last->type == PIPE)
	{
		syntax_error(last->data);
		return ;
	}
	while ((last = last->prev))
	{
		if(previous->type < PIPE && last->type < TEXT)
		{
			syntax_error(previous->data);
			return ;
		}
		if(previous->type == PIPE && last->type == EMPTY)
		{
			syntax_error(previous->data);
			return ;
		}
		if(previous->type <= SEMICOLON && last->type == SEMICOLON)
		{
			syntax_error(previous->data);
			return ;
		}
		previous = last;
	}

}

char *type(int type) //delete
{
	if(type == EMPTY)
		return strdup("EMPTY");
	else if(type == TEXT)
		return strdup("TEXT");
	else if(type ==  RED_RIGHT)
		return strdup("RED_RIGHT");
	else if(type ==  RED_DRIGHT)
		return strdup("RED_DRIGHT");
	else if(type ==  RED_LEFT)
		return strdup("RED_LEFT");
	else if(type == PIPE)
		return strdup("PIPE");
	else if(type == SEMICOLON)
		return strdup("SEMICOLON");
	else if(type == OR)
		return strdup("OR");
	else if(type == AND)
		return strdup("AND");
	else if(type == ENV)
		return strdup("ENV");
	else
		return strdup("ERROR TYPE");
}

char		**create_array(t_token **lst, int size)
{
	char	**arr;
	t_token	*tmp;
	int		i;

	tmp = *lst;
	i = 0;
	if (!(arr = malloc((size + 1) * sizeof(char *))))
		error_exit("malloc error");
	arr[size] = NULL;
	while (tmp)
	{

		printf("%-11s:  %s\n", type(tmp->type), tmp->data);
		if (!(arr[i] = malloc(tmp->len + 1)))
			error_exit("malloc error");
		ft_memcpy(arr[i], tmp->data, tmp->len);
		arr[i][tmp->len] = '\0';
		tmp = tmp->prev;
		i++;
	}
	return (arr);
}
void	parser(char *line, t_list **env)
{
	t_token	*tokens;


	tokens = parse_line(&line);
	tokens = token_last(tokens);
	//create_array(&tokens, token_lst_size(tokens));
	check_tokens(tokens);
	//tokens_handler(tokens, env);
	clear_tokens(&tokens, free);
	ft_lstclear(env, env_clear);
}
int	main(int argc, char **argv, char **env)
{
	t_list	*lenv;
	char	*line;

	int num;
	char **aaa;
	num = argc;
	aaa = argv;
	lenv = env_create(env);

	while (1)
	{
		ft_putstr_fd(PROMPT, 1);
		get_next_line(0, &line);
		parser(line, & lenv);
	}

	//sleep(20);
	return (0);
}


// int check_begin(char *str, int i)
// {
// 	int j;

// 	j = 0;
// 	while (j < i)
// 	{
// 		if (str[j] != ' ' && str[j] != '|')
// 			return (1);
// 	}
// 	return (0);
// }

// char is_valid(char *str)
// {
// 	int q;
// 	int dq;
// 	int i;
// 	char *cur;

// 	i = 0;
// 	q = 0;
// 	dq = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '|' && !q && !dq)
// 		{
// 			if (!check_begin(str, i))
// 				return ('|');
// 		}
// 	}
// 	return (0);
// }
