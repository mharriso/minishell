#include "libft.h"
#include "buildin.h"
#include "structs.h"
#include "fork.h"
#include "com_func.h"

static void	exec_command(char **command, t_list **env)
{
	int	res;

	res = ft_runbuildin(command, env);
	if (!res)
		exec_external(command, NULL, NULL, env);
}

void	commands_handler(t_list *com_list, t_list **env)
{
	char	**command;
	t_redir	*red;

	if (com_list->next)
		do_pipe(com_list, env);
	else
	{
		command = com_getcom(com_list);
		red = com_getredir(com_list);
		if (red)
			exec_external(command, red, NULL, env);
		else
			exec_command(command, env);
	}
}
