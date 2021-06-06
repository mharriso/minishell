#include "libft.h"
#include "buildin.h"
#include "structs.h"
#include "fork.h"
#include "com_func.h"

static int	exec_command(char **command, t_list **env)
{
	int	res;

	res = ft_runbuildin(command, env);
	if (res == -1)
		exec_external(command, NULL, NULL, env);
	return (res);
}

static int	get_exstatus(t_list *com_list)
{
	t_fork	*info;
	int		status;

	status = 0;
	while (com_list)
	{
		info = com_getinfo(com_list);
		if (info)
		{
			waitpid(info->pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				status = WTERMSIG(status);
				status += 128;
			}
			com_list = com_list->next;
		}
	}
	return (status);
}

//return value = exit status ($?)
int	commands_handler(t_list *com_list, t_list **env)
{
	char	**command;
	t_redir	*red;
	int		status;

	status = -1;
	if (com_list->next)
		do_pipe(com_list, env);
	else
	{
		command = com_getcom(com_list);
		red = com_getredir(com_list);
		if (red)
			exec_external(command, red, NULL, env);
		else
			status = exec_command(command, env);
	}
	if (status == -1)
		status = get_exstatus(com_list);
	return (status);
}
