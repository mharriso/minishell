#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "env_func.h"
#include "structs.h"
#include "ft_term.h"

#include "exit.h"
#include "env_func.h"
#include <string.h> //delete

#define BLUE "\033[34;1m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define ARROW "\U000027A1"
#define SHELL "\U0001F41A"
#define CROSS "\U0000274E"
#define DOLLAR GREEN"$"RESET
#define DIAMOND "\U0001F538"

static unsigned int g_ret;
void asd(char **env)
{
	t_list	*lenv;
	char	*line;

	lenv = env_create(env);


	//while(1)
	//{
		ft_putstr_fd(PROMPT, 1);
		get_next_line(0, &line);
		run_parser(line, &lenv);
	//}
	ft_lstclear(&lenv, env_clear);
}

int	main(int argc, char **argv, char **env)
{
	int num;
	char **aaa;
	num = argc;
	aaa = argv;

	asd(env);
	//printf("%d\n", g_ret);
	//sleep(15);
	return (0);
}
