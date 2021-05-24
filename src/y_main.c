#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "env_func.h"



int	main(int argc, char **argv, char **env)
{
	t_list	*lenv;
	char **tokens;
	char *line;

	int num;
	char **aaa;
	num = argc;
	aaa = argv;


	lenv = env_create(env);

	get_next_line(0, &line);
	tokens = parser(line);

	for (size_t i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	ft_lstclear(&lenv, env_clear);

	//sleep(20);
	return (0);
}
