#include <fcntl.h>
#include <stdlib.h>
#include "history.h"
#include "history_utils.h"
#include "exit.h"

static void	fill_history_fd(t_dlist **dlst, int fd)
{
	char	*line;
	char	*content;
	t_dlist	*node;
	int		res;

	line = NULL;
	res = get_next_line(fd, &line);
	while (res != 0 && res != -1)
	{
		content = ft_strdup(line);
		node = ft_dlstnew(content);
		if (!node)
			error_exit("fill_history_fd");
		ft_dlstadd_back(dlst, node);
		free(line);
		line = NULL;
		res = get_next_line(fd, &line);
	}
	free(line);
}

t_hisory	*history_init(const char *pname, t_list **env)
{
	t_hisory	*his;
	char		*msh_lvl;
	char		i;
	int			fd;

	his = malloc(sizeof(t_hisory));
	if (!his)
		error_exit("history_init");
	msh_lvl = history_get_shlvl(env);
	his->begin = NULL;
	i = '0';
	while (i <= *msh_lvl)
	{
		his->fname = history_get_fname(i, pname);
		fd = open(his->fname, O_RDONLY | O_CREAT, S_IREAD | S_IWRITE);
		if (i != *msh_lvl)
			free(his->fname);
		fill_history_fd(&(his->begin), fd);
		his->cur = his->begin;
		close(fd);
		i++;
	}
	free(msh_lvl);
	return (his);
}

void	history_free(t_hisory *history)
{
	ft_dlstclear(&(history->begin), free);
	free(history->fname);
	free(history);
}
