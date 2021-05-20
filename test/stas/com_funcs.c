#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <dirent.h>

#define RED_LEFT 1
#define RED_RIGHT 2
#define RED_DRIGHT 3

#define PIPE_IN 1
#define PIPE_OUT 3

typedef struct	s_list
{
	void	*content;
	void	*next;
}				t_list;


typedef struct	s_fdi
{
	int		fd[2];
	int		type;
}				t_fdi;

typedef struct	s_fork
{
	pid_t	pid;
	t_fdi	fd[2];
	int		pipe_type;
}				t_fork;

typedef struct	s_redir
{
	char	*fname;
	int		type;
	int		fd;
}				t_redir;

typedef struct	s_command
{
	char	**com;
	t_redir	*red;
	t_fork	*info;
	int		pipe_type;
}				t_command;

char	**com_getcom(t_list *list)
{
	return (((t_command*)list->content)->com);
}

t_redir	*com_getredir(t_list *list)
{
	return (((t_command*)list->content)->red);
}

int	com_getptype(t_list *list)
{
	return (((t_command*)list->content)->pipe_type);
}

t_fork	*com_getinfo(t_list *list)
{
	return (((t_command*)list->content)->info);
}

void	ft_dup(t_fdi *info)
{
	dup2(info->fd[info->type], info->type);
	close(info->fd[0]);
	close(info->fd[1]);
}

char	*ft_get_path(char *name)
{
	DIR				*dp;
	struct dirent	*ep;

	//TODO what is relative and absolute path?

	dp = opendir ('./');
	if (dp != NULL)
	{
		while (ep = readdir (dp))
			puts (ep->d_name);
		(void) closedir (dp);
	}
	else
		puts ('Couldnt open the directory.');
		return 0;

}

void ft_execve(char **commands, t_list **env)
{
	int		res;
	char	*path;
	char	**a_env;

	res = ft_runbuildin(commands, env);
	if (res)
		exit(1);//TODO what to return?
	path = ft_get_path(*commands);
	a_env = env_listtoarr_to_new(*env);
	execve(path, commands, a_env);
}

int	ft_redirect(char *fname, int red_type)
{
	int		fd;
	int		flags;
	int		dup_fd;

	dup_fd = 1;
	if (red_type == RED_LEFT)
	{
		flags = O_CREAT | O_RDONLY;
		dup_fd = 0;
	}
	else if (red_type == RED_RIGHT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (red_type == RED_DRIGHT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		return (-2);
	fd = open(fname, flags, S_IREAD | S_IWRITE);
	if (fd == -1)
		return (-1);
	dup2(fd, dup_fd);
	return (fd);
}

void	do_redirect(t_redir *red)
{
	if (!red)
		return ;
	while (red->type)
	{
		red->fd = ft_redirect(red->fname, red->type);
		red++;
	}
}

void	ft_fork(t_fork *info, char **commands, t_redir *red, t_list **env)
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
	ft_fork(info, command, red, env);
}

void	exec_command(char **command, t_list **env)
{
	int	res;

	res = ft_runbuildin(command, env);
	if (!res)
		exec_external(command, NULL, NULL, env);
}

t_fork	*make_tfork(t_list *temp)
{
	t_fork		*info;
	static int	temp_fd[2];

	info = malloc(sizeof(t_fork));
	info->pipe_type = com_getptype(temp);
	if (info->pipe_type & PIPE_IN)
	{
		info->fd[0].fd[0] = temp_fd[0];
		info->fd[0].fd[1] = temp_fd[1];
		info->fd[1].type = 0;
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

void	ft_pipe(t_list *com_list, t_list **env)
{
	t_list	*temp;
	t_redir	*red;
	char	**commands;

	temp = com_list;
	while (temp)
	{
		((t_command*)com_list->content)->info = make_tfork(temp);
		commands = com_getcom(temp);
		red = com_getredir(temp);
		exec_external(commands, red, ((t_command*)com_list->content)->info, env);
		temp = temp->next;
	}

}

void	commands_handler(t_list *com_list, t_list **env)
{
	char	**command;
	t_redir	*red;

	if (com_list->next)
		ft_pipe(com_list, env);
	else
	{
		command = com_getcom(com_list);
		red = com_getredir(com_list);
		do_redirect(red);
		exec_command(command, env);
		//TODO close all red->fd
	}
}
