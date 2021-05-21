#include <stdio.h>
#include "structs.h"
#include "libft.h"
#include "buildin.h"
#include "utils.h"
#include "env_func.h"
#include "fork.h"

static void	ft_dup(t_fdi *info)
{
	printf("info->fd[info->type] = %d, info->type = %d\n", info->fd[info->type], info->type);
	dup2(info->fd[info->type], info->type);
	close(info->fd[0]);
	close(info->fd[1]);
}

static void	ft_execve(char **commands, t_list **env)
{
	int		res;
	char	*path;
	char	**a_env;

	res = ft_runbuildin(commands, env);
	if (res)
		exit(0);//TODO what to return?
	path = get_full_path(*commands, *env);
	if (path)
	{
		a_env = env_listtoarr_to_new(*env);
		execve(path, commands, a_env);
	}
	else
	{
		printf("minishell: %s: command not found\n", *commands);
		exit(1);
	}
}

static void	do_fork(t_fork *info, char **commands, t_redir *red, t_list **env)
{
	info->pid = fork();
	if (!info->pid)
	{

		if (info->pipe_type & PIPE_IN)
			ft_dup(info->fd);
		printf("from do_fork\n");
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
		printf("from exec in\n");
	}
	printf("from exec out\n");
	do_fork(info, command, red, env);
}
