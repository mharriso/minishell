#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "com_func.h"
#include "fork.h"

#include <stdio.h>

static t_fork	*make_tfork(t_list *temp)
{
	t_fork		*info;
	static int	temp_fd[2];

	info = malloc(sizeof(t_fork));
	info->pipe_type = com_getptype(temp);
	if (info->pipe_type & PIPE_IN)
	{
		info->fd[0].fd[0] = temp_fd[0];
		info->fd[0].fd[1] = temp_fd[1];
		info->fd[0].type = 0;
	}
	if (info->pipe_type & PIPE_OUT)
	{
		pipe(info->fd[1].fd);
		temp_fd[0] = info->fd[1].fd[0];
		temp_fd[1] = info->fd[1].fd[1];
		info->fd[1].type = 1;
	}
	return (info);
}

static void	close_fd(t_list *com_list)
{
	t_fork	*info;

	while (com_list)
	{
		info = com_getinfo(com_list);
		if (info->pipe_type & PIPE_IN)
		{
			//printf("CLOSE IN: %d\n", info->pid);
			close(info->fd[0].fd[0]);
			close(info->fd[0].fd[1]);
		}
		if (info->pipe_type & PIPE_OUT)
		{
			//printf("CLOSE OUT: %d\n", info->pid);
			close(info->fd[1].fd[0]);
			close(info->fd[1].fd[1]);
		}
		com_list = com_list->next;
	}
}

void	do_pipe(t_list *com_list, t_list **env)
{
	t_list	*temp;
	t_redir	*red;
	char	**commands;

	temp = com_list;
	while (temp)
	{
		((t_command *)temp->content)->info = make_tfork(temp);
		commands = com_getcom(temp);
		red = com_getredir(temp);
		exec_external(temp, env);
		temp = temp->next;
	}
	close_fd(com_list);
}
