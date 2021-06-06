#include "env_func.h"
#include "buildin.h"
#include "ft_term.h"
#include <stdio.h>

static void	ms_run(int argc, char **argv, char **envp)
{
	t_list	*env;

	if (argc > 1)
	{
		printf("No args allow\n");
		return ;
	}
	env = env_create(envp);
	ft_term(argv[0], &env);
	ft_lstclear(&env, env_clear);
}

int	main(int argc, char **argv, char **envp)
{
	ms_run(argc, argv, envp);
	ft_exit(NULL);
	return (0);
}
