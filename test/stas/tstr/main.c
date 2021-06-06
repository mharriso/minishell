#include "tstr.h"
#include <stdio.h>

int	main()
{
	t_string *str;

	str = tstr_create();

	tstr_add(str, "Heallo! sdf");
	printf("%s\n", str->str);
	tstr_remove_at(str, 3);
	printf("%s\n", str->str);
	tstr_remove(str);
	printf("%s\n", str->str);
	tstr_remove(str);
	printf("%s\n", str->str);
	tstr_remove(str);
	printf("%s\n", str->str);
	tstr_remove(str);
	printf("%s\n", str->str);
	tstr_insert_size(str, 5, " World", 6);

	printf("%s\n", str->str);
	return (0);
}
