#include "libft.h"
#include "structs.h"
#include "exit.h"

int	env_name_check(char *str)
{
	int		res;

	res = ft_isalpha(*str) || *str == '_';
	while (*str != '\0' && res)
	{
		res = ft_isalnum(*str) || *str == '_';
		str++;
	}
	return (res);
}

static void	env_freecont(t_env *env)
{
	free(env->name);
	if (env->value)
		free(env->value);
}

void	env_clear(void *v)
{
	env_freecont((t_env *)v);
	free(v);
}

//return 1 if success
int	env_replace(const char *name, const char *value, t_list **env)
{
	t_list	*temp;
	int		res;

	temp = *env;
	while (temp)
	{
		res = ft_strcmp(name, ((t_env *)temp->content)->name);
		if (!res)
		{
			env_freecont((t_env *)temp->content);
			((t_env *)temp->content)->name = ft_strdup(name);
			((t_env *)temp->content)->value = ft_strdup(value);
			if (!((t_env *)temp->content)->name
				|| !((t_env *)temp->content)->value)
				error_exit("env_replace");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*str_env(const char *name, const char *value)
{
	size_t	i;
	char	*str;

	i = ft_strlen(name);
	i += ft_strlen(value);
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (*name)
	{
		str[i] = *name;
		name++;
		i++;
	}
	str[i++] = '=';
	while (*value)
	{
		str[i] = *value;
		value++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
