#include "env_func.h"
#include "exit.h"
#include "ft_term.h"
#include <stdio.h>

static void	ms_run(int argc, char **argv, char **envp)
{
	t_list	*env;
	int		ret;

	if (argc > 1)
	{
		printf("No args allow\n");
		return ;
	}
	env = env_create(envp);
	ret = ft_term(argv[0], &env);
	ft_lstclear(&env, env_clear);
	printf("exit\n");
	success_exit(ret);
}

int	main(int argc, char **argv, char **envp)
{
	ms_run(argc, argv, envp);
	return (0);
}
