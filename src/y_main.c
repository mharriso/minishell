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
	else
		return strdup("ERROR TYPE");
}

char		**create_array(t_token **head, int size)
{
	char	**arr;
	t_token	*tmp;

	tmp = *head;
	if (!(arr = malloc((size + 1) * sizeof(char *))))
		error_exit("malloc error");
	arr[size] = NULL;
	while (tmp)
	{
		size--;
		printf("%-11s:  |%s|\n", type(tmp->type), tmp->data); //delete
		if (!(arr[size] = malloc(tmp->len + 1)))
			error_exit("malloc error");
		ft_memcpy(arr[size], tmp->data, tmp->len);
		arr[size][tmp->len] = '\0';
		tmp = tmp->next;
	}
	return (arr);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*lenv;
	t_token *tokens;
	char *line;

	int num;
	char **aaa;
	num = argc;
	aaa = argv;

	lenv = env_create(env);
	while(1)
	{
		ft_putstr_fd(YELLOW ARROW BLUE" msh"RESET SHELL" "DIAMOND" ", 1);
		get_next_line(0, &line);
		tokens = parser(line, &lenv);
		create_array(&tokens, token_lst_size(tokens));
	}
	ft_lstclear(&lenv, env_clear);
	//sleep(20);
	return (0);
}
