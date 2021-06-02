#include "env_func.h"
#include "buildin.h"
#include "ft_term.h"

#include <stdlib.h>

void ft_run(int argc, char **argv, char **envp)
{
	t_list	*env;

	env = env_create(envp);

	if (argc >= 1)
		ft_term(argv[0], &env);

	ft_lstclear(&env, env_clear);
}

int	main(int argc, char **argv, char **envp)
{
	char **a;

	a = malloc(sizeof(char *) * 2);
	a[0] = ft_strdup("0");
	a[1] = NULL;
	ft_run(argc, argv,envp);
	ft_exit(a);
	return (0);
}
