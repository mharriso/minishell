#include <unistd.h>
#include <fcntl.h>
#include "structs.h"

static int	redirect(char *fname, int red_type)
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
		red->fd = redirect(red->fname, red->type);
		red++;
	}
}
