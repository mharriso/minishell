#include "libft.h"
#include "structs.h"
#include "exit.h"

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

//commands must be NULL terminated
//red[last] must have fname = NULL (use red_create_last), type = 0,
//red can be NULL
t_command	*com_create(char **commands, t_redir *red, int pipe_type)
{
	t_command	*com;

	com = malloc(sizeof(t_command));
	if (!com)
		error_exit("com_create\n");
	com->com = commands;
	com->pipe_type = pipe_type;
	com->red = red;
	return (com);
}

void	com_clear(void *command)
{
	t_command	*c;
	int			i;

	i = 0;
	c = command;
	while ((c->com)[i])
	{
		free((c->com)[i]);
		i++;
	}
	free(c->com);
	if (c->info)
		free(c->info);
	i = 0;
	if (c->red)
	{
		while ((c->red)[i].fname)
		{
			free((c->red)[i].fname);
			i++;
		}
		free(c->red);
	}
	free(command);
}
