#include <fcntl.h>
#include <stdlib.h>
#include "history.h"
#include "history_utils.h"
#include "exit.h"

static unsigned int	g_hsize;

static void	fill_history_fd(t_dlist **dlst, int fd, int is_cur)
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
		if (is_cur)
			g_hsize++;
		free(line);
		line = NULL;
		res = get_next_line(fd, &line);
	}
	free(line);
}

static t_hisory	*his_malloc(void)
{
	t_hisory	*his;

	his = malloc(sizeof(t_hisory));
	if (!his)
		error_exit("history_init");
	his->begin = NULL;
	return (his);
}

t_hisory	*history_init(const char *pname, t_list **env)
{
	t_hisory	*his;
	char		*msh_lvl;
	char		*fname;
	char		i;
	int			fd;

	his = his_malloc();
	msh_lvl = history_get_shlvl(env);
	i = *msh_lvl;
	while (i >= '0')
	{
		fname = history_get_fname(i, pname);
		fd = open(fname, O_RDONLY | O_CREAT, S_IREAD | S_IWRITE);
		if (i != *msh_lvl)
			free(fname);
		else
			his->fname = fname;
		fill_history_fd(&(his->begin), fd, i == *msh_lvl);
		his->cur = his->begin;
		close(fd);
		i--;
	}
	free(msh_lvl);
	return (his);
}

static void	history_save(const char *fname, t_dlist *history)
{
	int				fd;
	unsigned int	i;

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC);
	i = 0;
	while (i < g_hsize)
	{
		ft_putstr_fd((char *)history->content, fd);
		write(fd, "\n", 1);
		history = history->next;
		i++;
	}
	close(fd);
}

void	history_add(const char *fname, const char *content, t_dlist **history)
{
	t_dlist	*node;

	if (!history || !content)
		return ;
	if (*history && (*history)->content \
		&& !ft_strcmp((*history)->content, content))
		return ;
	node = ft_dlstnew(ft_strdup(content));
	if (!node)
		error_exit("history_add");
	ft_dlstadd_front(history, node);
	g_hsize++;
	history_save(fname, *history);
}
