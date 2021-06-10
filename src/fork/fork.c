#include <stdio.h>
#include <sys/stat.h>
#include "structs.h"
#include "libft.h"
#include "buildin.h"
#include "utils.h"
#include "env_func.h"
#include "fork.h"
#include "com_func.h"
#include "ft_signal.h"

static void	execute_func(char *path, char **commands, t_list *env)
{
	char		**a_env;
	struct stat	buf;

	if (!stat(path, &buf))
	{
		if (buf.st_mode & S_IEXEC)
		{
			a_env = env_listtoarr_to_new(env);
			execve(path, commands, a_env);
		}
		else
		{
			print_error(*commands, ": not a exec file\n");
			exit(126);
		}
	}
	exit(127);
}

static void	ft_execve(char **commands, t_list **env)
{
	int			res;
	char		*path;

	res = ft_runbuildin(commands, env);
	if (res != -1)
		exit(res);
	path = get_full_path(*commands, *env);
	if (path)
		execute_func(path, commands, *env);
	else
	{
		print_error(*commands, ": command not found\n");
		exit(127);
	}
}

static void	close_all(t_list *beg)
{
	t_fork	*info;

	while (beg)
	{
		info = com_getinfo(beg);
		if (info)
		{
			if (info->pipe_type & PIPE_IN)
			{
				close(info->fd->fd[0]);
				close(info->fd->fd[1]);
			}
			if (info->pipe_type & PIPE_OUT)
			{
				close((info->fd + 1)->fd[0]);
				close((info->fd + 1)->fd[1]);
			}
		}
		beg = beg->next;
	}
}

static void	do_fork(t_fork *info, t_command *cmd, t_list **env, t_list *com_beg)
{
	info->pid = fork();
	if (!info->pid)
	{
		sig_restore();
		if (info->pipe_type & PIPE_IN)
			dup2(info->fd->fd[info->fd->type], info->fd->type);
		if (info->pipe_type & PIPE_OUT)
			dup2((info->fd + 1)->fd[(info->fd + 1)->type], \
				(info->fd + 1)->type);
		close_all(com_beg);
		do_redirect(cmd->red);
		ft_execve(cmd->com, env);
	}
}

void	exec_external(t_list *com_list, t_list **env, t_list *com_beg)
{
	t_command	*cmd;

	cmd = com_list->content;
	if (!cmd->info)
	{
		cmd->info = malloc(sizeof(t_fork));
		cmd->info->pipe_type = 0;
	}
	do_fork(cmd->info, cmd, env, com_beg);
}
