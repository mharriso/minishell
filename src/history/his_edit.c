#include <fcntl.h>
#include "libft.h"
#include "dlist.h"
#include "exit.h"

char	*history_up_arrow(t_dlist **cur_history)
{
	char	*his_line;

	if (!cur_history || !*cur_history)
		return (NULL);
	his_line = (*cur_history)->content;
	if ((*cur_history)->next)
		*cur_history = (*cur_history)->next;
	return (his_line);
}

char	*history_down_arrow(t_dlist **cur_history)
{
	char	*his_line;

	his_line = NULL;
	if (!cur_history || !*cur_history)
		return (his_line);
	if ((*cur_history)->prew && (*cur_history)->prew->prew)
	{
		*cur_history = (*cur_history)->prew;
		his_line = (*cur_history)->prew->content;
	}
	return (his_line);
}

void	history_add(const char *content, t_dlist **history)
{
	t_dlist	*node;

	if (!history || !*history || !(*history)->content || !content)
		return ;
	if (!ft_strcmp((*history)->content, content))
		return ;
	node = ft_dlstnew(ft_strdup(content));
	if (!node)
		error_exit("history_add");
	ft_dlstadd_front(history, node);
}

void	history_save(const char *fname, t_dlist *history)
{
	int		fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC);
	while (history)
	{
		ft_putstr_fd((char *)history->content, fd);
		write(fd, "\n", 1);
		history = history->next;
	}
	close(fd);
}
