#include "buildin.h"
#include "env_func.h"
#include "exit.h"
#include <stdio.h>

static char	*set_lvl(t_list **env)
{
	char	*msh[2];

	msh[0] = ft_strdup("MINISHLVL=0");
	msh[1] = NULL;
	ft_export(msh, env);
	free(msh[0]);
	return (ft_strdup("0"));
}

static char	*get_lvl(char *lvl)
{
	if (*lvl < '9')
		(*lvl)++;
	else
	{
		printf("minishell: max mshlvl is 9, history will be override\n");
		*lvl = '0';
	}
	return (ft_strdup(lvl));
}

char	*history_get_shlvl(t_list **env)
{
	char	*lvl;

	lvl = env_getvaluebyname("MINISHLVL", *env);
	if (!lvl)
	{
		lvl = set_lvl(env);
		if (!lvl)
			error_exit("history_get_shlvl");
	}
	else
		lvl = get_lvl(lvl);
	return (lvl);
}
