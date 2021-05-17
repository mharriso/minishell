#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

int	main()
{
	char **tokens;

	tokens = parser("123 hello 444");
	for (size_t i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	return (0);
}
