/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuliean <tjuliean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:32:03 by tjuliean          #+#    #+#             */
/*   Updated: 2021/05/21 17:22:08 by tjuliean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "structs.h"
#include "env_func.h"
#include "buildin.h"
#include "utils.h"
#include "fork.h"

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
	red[0].fname = ft_strdup("a");
	red[0].type = RED_DRIGHT;
	red[1].fname = ft_strdup("b");
	red[1].type = RED_LEFT;
	red[2].fname = NULL;
	red[2].type = 0;

	return red;
}

t_list	*create_cmd()
{
	t_command	*cmd;
	t_list		*lst;
	t_list		*node;
	char		**com;

	cmd = malloc(sizeof(t_command));
	com = malloc(sizeof(char*) * 2);
	com[0] = ft_strdup("yes");
	com[1] = NULL;
	cmd->com = com;
	cmd->red = NULL;
	cmd->pipe_type = PIPE_OUT;
	lst = ft_lstnew(cmd);

	cmd = malloc(sizeof(t_command));
	com = malloc(sizeof(char*) * 2);
	com[0] = ft_strdup("head");
	com[1] = NULL;
	cmd->com = com;
	cmd->red = NULL;
	cmd->pipe_type = PIPE_IN;
	node = ft_lstnew(cmd);
	ft_lstadd_back(&lst, node);

	return (lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	// t_redir	*red;
	t_list	*cmd_list;

	char **a;
	a = argv;

	env = env_create(envp);

	if (argc > 1)
	{
		cmd_list = create_cmd();
		do_pipe(cmd_list, &env);
		//exec_external(argv + 1, NULL, NULL, &env);
	}
	printf("in the end\n");
	ft_lstclear(&env, env_clear);
	return (0);
}
