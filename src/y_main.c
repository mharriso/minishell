#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

int	main()
{
	char **tokens;
	char *line;

	get_next_line(0, &line);
	tokens = parser(line);
	for (size_t i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);

	return (0);
}
