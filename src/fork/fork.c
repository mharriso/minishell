#include <stdio.h>
#include <sys/stat.h>
#include "structs.h"
#include "libft.h"
#include "buildin.h"
#include "utils.h"
#include "env_func.h"
#include "fork.h"

static void	ft_dup(t_fdi *info)
{
	dup2(info->fd[info->type], info->type);
	close(info->fd[0]);
	close(info->fd[1]);
}

static void	ft_execve(char **commands, t_list **env)
{
	int			res;
	char		*path;
	char		**a_env;
	struct stat	buf;

	res = ft_runbuildin(commands, env);
	if (res != -1)
		exit(res);
	path = get_full_path(*commands, *env);
	if (path)
	{
		res = stat("child.exe", &buf);
		if (res == 0)
		{
			if (buf.st_mode & S_IEXEC)
			{
				a_env = env_listtoarr_to_new(*env);
				execve(path, commands, a_env);
			}
			else
			{
				printf("minishell: %s: not a exec file\n", *commands);
				exit(126);
			}
		}
		exit(127);
	}
	else
	{
		printf("minishell: %s: command not found\n", *commands);
		exit(127);
	}
}

static void	do_fork(t_fork *info, char **commands, t_redir *red, t_list **env)
{
	info->pid = fork();
	if (!info->pid)
	{

		if (info->pipe_type & PIPE_IN)
			ft_dup(info->fd);
		if (info->pipe_type & PIPE_OUT)
			ft_dup(info->fd + 1);
		do_redirect(red);
		ft_execve(commands, env);
	}
}

void	exec_external(char **command, t_redir *red, t_fork *info, t_list **env)
{
	if (!info)
	{
		info = malloc(sizeof(t_fork));
		info->pipe_type = 0;
	}
	do_fork(info, command, red, env);
}
