/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:32:03 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/24 15:16:12 by tjuliean         ###   ########.fr       */
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

	com = malloc(sizeof(char*) * 2);
	com[0] = ft_strdup("pwd");
	com[1] = NULL;
	lst = ft_lstnew(com_create(com, NULL, PIPE_OUT));

	com = malloc(sizeof(char*) * 2);
	com[0] = ft_strdup("cat");
	com[1] = NULL;
	node = ft_lstnew(com_create(com, NULL, PIPE_IN));
	ft_lstadd_back(&lst, node);

	return (lst);
}

void ft_run(int argc, char **argv, char **envp)
{
	t_list	*env;
	t_list	*cmd_list;

	char **a;
	a = argv;

	env = env_create(envp);

	if (argc >= 1)
	{
		cmd_list = create_cmd();
		commands_handler(cmd_list, &env);
		ft_lstclear(&cmd_list, com_clear);
	}
	ft_lstclear(&env, env_clear);
}

int	main(int argc, char **argv, char **envp)
{
	ft_run(argc, argv,envp);
	return (0);
}
