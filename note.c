#include <stdlib.h>
#include "libft.h"
#include "com_func.h"
#include "red_func.h"
#include "structs.h"

// void	commands_handler(t_list *com_list, t_list **env);

void to_use_commands(t_list **env)
{
	t_list		*commands;
	t_list		*node;
	t_command	*cmd;
	t_redir		*red;

	red = malloc(sizeof(t_redir) * (count + 1)); // count = 2;
	red[0] = red_create("a.txt", RED_LEFT);
	red[1] = red_create("b.txt", RED_DRIGHT);
	red[2] = red_create_last();
	// | \0
	// < >
	cmd = com_create({"echo", "-n", "hello", NULL}, red, PIPE_OUT);
	commands = ft_lstnew(cmd);

	cmd = com_create({"cat", NULL}, NULL, PIPE_IN);
	node = ft_lstnew(cmd);
	ft_lstadd_back(&commands, node);

	commands_handler(commands, env);

	ft_lstclear(&commands, com_clear);
}

// 258 bash: syntax error near unexpected token `|' `;' `>' `<' `>>'
// export www='ls -la'
// в двойных ковычках экранируется " \ 
