/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:32:03 by tjuliean          #+#    #+#             */
/*   Updated: 2021/06/11 14:29:40 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "structs.h"
#include "env_func.h"
#include "buildin.h"
#include "utils.h"
#include "fork.h"
#include "com_func.h"
#include "red_func.h"
#include "ft_term.h"
#include "parser.h"

// static char	**fill_arg(int argc, char **argv)
// {
// 	char	**arg;

// 	arg = malloc(sizeof(char*) * argc);
// 	for (int i = 1; i < argc; i++)
// 		arg[i - 1] = argv[i];
// 	arg[argc - 1] = NULL;

// 	return (arg);
// }

t_redir *create_red()
{
	t_redir *red;

	red = malloc(sizeof(t_redir) * 3);
	red[0] = red_create(ft_strdup("a"), RED_RIGHT);
	red[1] = red_create(ft_strdup("b"), RED_RIGHT);
	red[2] = red_create_last();

	return red;
}

t_list	*create_cmd()
{
	t_list		*lst;
	t_list		*node;
	char		**com;

	// com = malloc(sizeof(char*) * 2);
	// com[0] = ft_strdup("asd");
	// com[1] = NULL;
	// lst = ft_lstnew(com_create(com, NULL, PIPE_OUT));

	com = malloc(sizeof(char*) * 2);
	com[0] = ft_strdup("yes");
	com[1] = NULL;
	lst = ft_lstnew(com_create(com, NULL, PIPE_OUT));

	com = malloc(sizeof(char*) * 2);
	com[0] = ft_strdup("head");
	com[1] = NULL;
	node = ft_lstnew(com_create(com, NULL, PIPE_IN | PIPE_OUT));
	ft_lstadd_back(&lst, node);

	com = malloc(sizeof(char*) * 3);
	com[0] = ft_strdup("cat");
	com[1] = ft_strdup("-e");
	com[2] = NULL;
	node = ft_lstnew(com_create(com, NULL, PIPE_IN));
	ft_lstadd_back(&lst, node);

	return (lst);
}

void pr_tok(t_token *tk)
{
	while (tk)
	{
		printf("|%s|\n", tk->data);
		tk = tk->next;
	}

}

void ft_run(int argc, char **argv, char **envp)
{
	t_list	*env;
	//t_list	*cmd_list;

	t_token *tk;

	char **a;
	a = argv;

	env = env_create(envp);

	if (argc == 2)
	{
		// cmd_list = create_cmd();
		// commands_handler(cmd_list, &env);
		// ft_lstclear(&cmd_list, com_clear);

		//ft_term(argv[0], &env);

		tk = ft_wildcard("*.c");
		if (!tk)
			printf("null\n");
		else
		{
			pr_tok(tk);
		}
	}

	ft_lstclear(&env, env_clear);
}

int	main(int argc, char **argv, char **envp)
{
	// char **a;

	// a = malloc(sizeof(char *) * 2);
	// a[0] = ft_strdup("0");
	// a[1] = NULL;
	ft_run(argc, argv,envp);
	ft_exit(NULL);
	//sleep(10);
	return (0);
}
