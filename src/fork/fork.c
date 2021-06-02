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

static void print_error(const char *name, const char *msg)
{
	char	*str;
	char	*temp;
	int		len;

	temp = ft_strjoin("minishell: ", name);
	str = ft_strjoin(temp, msg);
	len = ft_strlen(str);
	write(2, str, len);
	free(temp);
	free(str);
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
		res = stat(path, &buf);
		if (res == 0)
		{
			if (buf.st_mode & S_IEXEC)
			{
				a_env = env_listtoarr_to_new(*env);
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
	else
	{
		print_error(*commands, ": command not found\n");
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
