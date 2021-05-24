#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "env_func.h"

static void	free_maxtix(char **m)
{
	size_t	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

static char	*find_in_dir(const char *name, DIR *dp, char *path)
{
	struct dirent	*ep;
	char			*full_path;
	char			*temp;
	int				res;

	ep = readdir(dp);
	while (ep)
	{
		res = ft_strcmp(name, ep->d_name);
		if (!res)
		{
			temp = ft_strjoin(path, "/");
			full_path = ft_strjoin(temp, name);
			free(temp);
			return (full_path);
		}
		ep = readdir(dp);
	}
	return (NULL);
}

static char	*find_by_paths(const char *name, char **paths)
{
	DIR		*dp;
	char	*full_path;

	while (*paths)
	{
		dp = opendir(*paths);
		if (dp != NULL)
		{
			full_path = find_in_dir(name, dp, *paths);
			closedir(dp);
			if (full_path)
				return (full_path);
		}
		paths++;
	}
	return (NULL);
}

char	*get_full_path(const char *name, t_list *env)
{
	char	**paths;
	char	*env_path;
	char	*full_path;

	if (*name == '/' || *name == '.')
	{
		full_path = ft_strdup(name);
		return (full_path);
	}
	env_path = env_getvaluebyname("PATH", env);
	paths = ft_split(env_path, ':');
	full_path = find_by_paths(name, paths);
	free_maxtix(paths);
	return (full_path);
}
