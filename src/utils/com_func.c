#include "libft.h"
#include "structs.h"

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
