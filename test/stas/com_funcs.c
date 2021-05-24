#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "env_func.h"
#include "utils.h"
#include "com_func.h"
#include "structs.h"


void	exec_command(char **command, t_list **env)
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
		do_redirect(red); // TODO must be in fork
		exec_command(command, env);
	}
}
