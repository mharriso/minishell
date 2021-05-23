#include <stdlib.h>

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

typedef struct	s_redir
{
	char	*fname;
	int		type;
}				t_redir;

typedef struct	s_command
{
	char	**com;
	t_redir	*red;
	int		pipe_type;
}				t_command;

char	**com_getcom(t_list *list)
{
	return ((t_command*)list->content)->com;
}

t_redir	*com_getredir(t_list *list)
{
	return ((t_command*)list->content)->red;
}

int	com_getptype(t_list *list)
{
	return ((t_command*)list->content)->pipe_type;
}

void	exec_external(char **command)
{
	//TODO check $PATH, absolute path, relative path and launch
}

void	exec_command(char **command, t_list *env)
{
	int	res;

	res = exec_buildin(command);
	if (!res)
		exec_external(command, env);
}

void	ft_redirect(char *fname, int mode, int is_right)
{
	int fd;

	fd = open(fname, mode);
	//if (is_right)

}

void	do_redirect(t_redir *red, char **command, t_list *env)
{

}

void	commands_handler(t_list *com_list, t_list *env)
{
	char	**command;
	t_redir	*red;

	if (com_list->next)
		do_fork(com_list, env);
	else
	{
		command = com_getcom(com_list);
		red = com_getredir(com_list);
		if (red)
			do_redirect(red, command, env);
		else
			exec_command(command, env);
	}
}

void asd()
{
	t_list		*commands;
	t_list		*temp_comm;
	t_command	*command;
	t_redir		*red;

	// asdfasd ftfg < file1 >> text.txt | cat -e
	command = malloc(sizeof(t_command));
	command->com = [asdfasd][ftfg];

	red = malloc(sizeof(t_redir) * (amount_of_redir + 1));
	red[0].fname = "file1";
	red[0].type = RED_LEFT;
	red[1].fname = "text.txt";
	red[1].type = RED_DRIGHT;
	red[2].type = 0;

	command->red = red;
	command->pipe_type = PIPE_OUT;
	commands = ft_lstnew(command);

	command = malloc(sizeof(t_command));
	command->com = [cat][-e];
	command->red = NULL;
	command->pipe_type = PIPE_IN;
	temp_comm = ft_lstnew(command);
	ft_lstaddback(&commands, temp_comm);

	commands_handler(commands, env);
}
