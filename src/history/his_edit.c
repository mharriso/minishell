#include <fcntl.h>
#include "libft.h"
#include "dlist.h"
#include "exit.h"

#include <stdio.h>

char	*history_up_arrow(t_dlist **cur_history)
{
	char	*his_line;

	his_line = NULL;
	if (!cur_history || !*cur_history)
		return (his_line);
	his_line = (*cur_history)->content;
	if ((*cur_history)->next)
		*cur_history = (*cur_history)->next;
	return (his_line);
}

char	*history_down_arrow(t_dlist **cur_history, char *cur_line)
{
	char	*his_line;

	his_line = NULL;
	if (!cur_history || !*cur_history)
		return (his_line);
	if ((*cur_history)->prew)
	{
		if (!(*cur_history)->next
			&& !ft_strcmp(cur_line, (*cur_history)->content))
		{
			his_line = (*cur_history)->prew->content;
		}
		else
		{
			*cur_history = (*cur_history)->prew;
			if ((*cur_history)->prew)
				his_line = (*cur_history)->prew->content;
		}
	}
	return (his_line);
}
