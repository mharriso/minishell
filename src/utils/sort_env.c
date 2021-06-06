#include <stdio.h>
#include "libft.h"

static void	print_env(char **env)
{
	while (*env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
}

void	sort_env(char **env)
{
	int		i;
	int		flag;
	int		res;
	char	*temp;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (env[i] && env[i + 1])
		{
			res = ft_strcmp(env[i], env[i + 1]);
			if (res > 0)
			{
				flag = 1;
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
	}
	print_env(env);
}
