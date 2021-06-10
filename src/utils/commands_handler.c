#include "libft.h"
#include "buildin.h"
#include "structs.h"
#include "fork.h"
#include "com_func.h"
#include "ft_term.h"
#include "exit.h"

#include <stdio.h>

static int	exec_command(t_list *com_list, t_list **env)
{
	int	res;

	res = ft_runbuildin(com_getcom(com_list), env);
	if (res == -1)
		exec_external(com_list, env, com_list);
	return (res);
}

static void	status_handler(int status)
{
	if (status == SIGQUIT)
		printf("Quit: %d\n", status);
	else if (status == SIGINT)
		printf("\n");
	else if (status == SIGTERM)
		printf("Terminate: %d\n", status);
	else if (status == SIGKILL)
		printf("Kill: %d\n", status);
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
				status_handler(status);
				status += 128;
			}
		}
		com_list = com_list->next;
	}
	return (status);
}

//return value = exit status ($?)
int	commands_handler(t_list *com_list, t_list **env)
{
	char	**command;
	t_redir	*red;
	int		status;

	restor_params();
	status = -1;
	if (com_list->next)
		do_pipe(com_list, env);
	else
	{
		command = com_getcom(com_list);
		red = com_getredir(com_list);
		if (red)
			exec_external(com_list, env, com_list);
		else
			status = exec_command(com_list, env);
	}
	if (status == -1)
		status = get_exstatus(com_list);
	term_set_attr();
	return (status);
}
