#include "libft.h"
#include "structs.h"
#include "exit.h"

char	*e_name(t_list *env)
{
	return (((t_env *)env->content)->name);
}

char	*e_value(t_list *env)
{
	return (((t_env *)env->content)->value);
}

char	*env_getname(char *str)
{
	char	*begin;
	char	*name;

	begin = str;
	while (*str != '=' && *str != '\0')
		str++;
	if (*str == '\0')
		return (NULL);
	*str = '\0';
	name = ft_strdup(begin);
	if (!name)
		error_exit("env_getname");
	*str = '=';
	return (name);
}

char	*env_getvalue(char *str)
{
	char	*value;

	while (*str != '=' && *str != '\0')
		str++;
	if (*str == '\0')
		return (NULL);
	*str = '\0';
	value = ft_strdup(str + 1);
	if (!value)
		error_exit("env_getnvalue");
	*str = '=';
	return (value);
}

char	*env_getvaluebyname(const char *name, t_list *env)
{
	char	*env_name;
	int		res;

	while (env)
	{
		env_name = e_name(env);
		res = ft_strcmp(name, env_name);
		if (!res)
			return (e_value(env));
		env = env->next;
	}
	return (NULL);
}
