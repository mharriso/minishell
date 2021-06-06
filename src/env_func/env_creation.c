#include "libft.h"
#include "structs.h"
#include "exit.h"
#include "env_func.h"

t_list	*env_create(char **env)
{
	t_list	*list;
	t_list	*node;
	t_env	*content;

	list = NULL;
	while (*env)
	{
		content = (t_env *)malloc(sizeof(t_env));
		content->name = env_getname(*env);
		if (ft_strcmp("OLDPWD", content->name))
			content->value = env_getvalue(*env);
		else
			content->value = NULL;
		node = ft_lstnew(content);
		ft_lstadd_back(&list, node);
		env++;
	}
	return (list);
}

char	**env_listtoarr(t_list *env)
{
	char	**new_env;
	char	*value;
	char	*name;
	int		i;

	i = ft_lstsize(env);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		error_exit("env_listtoarr\n");
	i = 0;
	while (env)
	{
		name = e_name(env);
		value = e_value(env);
		if (value)
			new_env[i] = str_env(name, value);
		else
			new_env[i] = ft_strdup(name);
		if (!new_env[i])
			error_exit("env_listtoarr\n");
		i++;
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

static int	lstsize_wo_v(t_list *lst)
{
	int		i;
	char	*value;

	i = 0;
	while (lst)
	{
		value = e_value(lst);
		if (value)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**env_listtoarr_to_new(t_list *env)
{
	char	**new_env;
	char	*value;
	char	*name;
	int		i;

	i = lstsize_wo_v(env);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		error_exit("env_listtoarr\n");
	i = 0;
	while (env)
	{
		name = e_name(env);
		value = e_value(env);
		if (value)
		{
			new_env[i] = str_env(name, value);
			if (!new_env[i])
				error_exit("env_listtoarr\n");
			i++;
		}
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
