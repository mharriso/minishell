#include <unistd.h>
#include <fcntl.h>
#include "env_func.h"
#include "buildin.h"
#include "libft.h"

#include <stdio.h>

#define HISTORY_FNAME "history/history_term"

typedef struct	s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prew;
}				t_dlist;

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*node;

	node = (t_dlist*)malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prew = NULL;
	return (node);
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		ft_dlstsize(t_dlist *lst)
{
	int	res;

	if (!lst)
		return (0);
	res = 1;
	while (lst->next)
	{
		res++;
		lst = lst->next;
	}
	return (res);
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		last = ft_dlstlast(*lst);
		last->next = new;
		new->prew = last;
	}
	else
		*lst = new;
}

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		(*lst)->prew = new;
	new->next = *lst;
	*lst = new;
}

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_dlstdelone(t_dlist *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*temp;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_dlstdelone(temp, del);
	}
	lst = (void*)0;
}
char	*get_path_to_ms(const char *str)
{
	char		*last;
	size_t		len;

	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '.')
	{
		str++;
		if (*str == '/')
			str++;
	}
	last = ft_strrchr(str, '/');
	if (!last)
		return (NULL);
	len = last - str + 1;
	last = malloc(len + 1);
	ft_memcpy(last, str, len);
	return (last);
}

char *get_abs_path(char *pname)
{
	char	*path;
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 512);
	temp = ft_strjoin(pwd, "/");
	free(pwd);
	pwd = get_path_to_ms(pname);
	printf("pwd = %s\n", pwd);
	if (pwd)
	{
		path = ft_strjoin(temp, pwd);
		free(pwd);
		free(temp);
	}
	else
		path = temp;
	return (path);
}

char	*history_get_fname(char *term_num, char *pname)
{
	char	*str;
	char	*temp;

	str = get_abs_path(pname);
	temp = ft_strjoin(str, HISTORY_FNAME);
	free(str);
	str = ft_strjoin(temp, term_num);
	free(temp);
	return (str);
}

char	*history_get_shlvl(t_list **env)
{
	char	*lvl;
	char	*tmp;
	char	*msh[2];

	lvl = env_getvaluebyname("MINISHLVL", *env);
	if (!lvl)
	{
		msh[0] = ft_strdup("MINISHLVL=0");
		msh[1] = NULL;
		ft_export(msh, env);
		free(msh[0]);
		lvl = ft_strdup("0");
		if (!lvl)
			exit(EXIT_FAILURE);
	}
	else
	{
		tmp = lvl;
		lvl = ft_strdup(lvl);
		if (*tmp < '9')
			(*tmp)++;
		else
		{
			printf("minishell: max mshlvl is 9, history will be override\n");
			*tmp = '0';
		}
	}
	return (lvl);
}

t_dlist	*history_init(char *pname, char **fname, t_list **env)
{
	int fd;
	int	res;
	char *line;
	char *content;
	char *fname;
	char	*i;
	char *msh_lvl;
	t_dlist	*dlst;
	t_dlist	*node;

	msh_lvl = history_get_shlvl(env);
	dlst = NULL;
	i = ft_strdup("0");
	if (!i)
		exit(EXIT_FAILURE);
	while (*i <= *msh_lvl)
	{
		*fname = history_get_fname(i, pname);
		fd = open(*fname, O_RDONLY | O_CREAT, S_IREAD | S_IWRITE);
		if (*i != *msh_lvl)
			free(*fname);
		line = NULL;
		res = get_next_line(fd, &line);
		while (res != 0 && res != -1)
		{
			content = ft_strdup(line);
			node = ft_dlstnew(content);
			if (!node)
				exit(EXIT_FAILURE);
			ft_dlstadd_back(&dlst, node);
			free(line);
			line = NULL;
			res = get_next_line(fd, &line);
		}
		close(fd);
		(*i)++;
	}

	return (dlst);
}

void	on_up_arrow(t_dlist **cur_history)
{
	if (!cur_history || !*cur_history)
		return ;
	//TODO clear line
	ft_putstr_fd((char*)(*cur_history)->content, 1);
	if ((*cur_history)->next)
		*cur_history = (*cur_history)->next;
}

void	on_down_arrow(t_dlist **cur_history)
{
	if (!cur_history || !*cur_history)
		return ;
	if ((*cur_history)->prew && (*cur_history)->prew->prew)
	{
		*cur_history = (*cur_history)->prew;
		//TODO clear line
		ft_putstr_fd((char*)((*cur_history)->prew->content), 1);
	}
}

void	history_add(char *content, t_dlist **history)
{
	t_dlist	*node;

	node = ft_dlstnew(ft_strdup(content));
	if (!node)
		exit(EXIT_FAILURE);
	ft_dlstadd_front(history, node);
}

void	history_save(char *fname, t_dlist *history)
{
	char	*line;
	int		fd;

	printf("%s", fname);

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC);
	while (history)
	{
		ft_putstr_fd((char*)history->content, fd);
		write(fd, "\n", 1);
		history = history->next;
	}
	close(fd);
}

void	test_history(char *pname, t_list **env)
{
	t_dlist	*cur_history;
	t_dlist	*begin_history;
	char	*line;
	char	*fname;

	begin_history = history_init(pname, &fname, env);
	cur_history = begin_history;
	line = NULL;
	while (get_next_line(0, &line))
	{

		if (!ft_strcmp(line, "up"))
			on_up_arrow(&cur_history);
		else if (!ft_strcmp(line, "down"))
			on_down_arrow(&cur_history);
		else if (!ft_strcmp(line, "exit"))
			break;
		else
		{
			history_add(line, &begin_history);
			cur_history = begin_history;
		}
		free(line);
		line = NULL;
	}
	history_save(fname, begin_history);
	ft_dlstclear(&begin_history, free);
}

int	main(int argc, char **argv)
{
	char *p;
	if (argc == 2)
		test_history(argv[1], argv[0]);
	return (0);
}
