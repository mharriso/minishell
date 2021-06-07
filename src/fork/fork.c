#include <stdio.h>
#include <sys/stat.h>
#include "structs.h"
#include "libft.h"
#include "buildin.h"
#include "utils.h"
#include "env_func.h"
#include "fork.h"
#include "com_func.h"

static void	ft_dup_close(t_fdi *info)
{
	close(info->fd[0]);
	close(info->fd[1]);
}

static void	ft_dup(t_fdi *info)
{
	dup2(info->fd[info->type], info->type);
	// close(info->fd[0]);
	// close(info->fd[1]);
}

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

void cloose(t_list *beg)
{
	t_fork	*info;

	while (beg)
	{
		info = com_getinfo(beg);
		if (info)
		{
			if (info->pipe_type & PIPE_IN)
				ft_dup_close(info->fd);
			if (info->pipe_type & PIPE_OUT)
				ft_dup_close(info->fd + 1);
		}
		beg = beg->next;
	}
}

static void	do_fork(t_fork *info, char **commands, t_redir *red, t_list **env, t_list *com_beg)
{
	info->pid = fork();
	if (!info->pid)
	{
		if (info->pipe_type & PIPE_IN)
			ft_dup(info->fd);
		if (info->pipe_type & PIPE_OUT)
			ft_dup(info->fd + 1);
		cloose(com_beg);
		do_redirect(red);
		ft_execve(commands, env);
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
	do_fork(cmd->info, cmd->com, cmd->red, env, com_beg);
}
