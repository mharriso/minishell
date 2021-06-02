#include "tstr.h"

//return 0 if success, 1 - malloc error
int	tstr_init(t_string *string)
{
	string->len = 4;
	string->str = malloc(string->len + 1);
	if (!string->str)
		return (1);
	*(string->str) = '\0';
	string->pos = 0;
	return (0);
}

//return NULL if malloc error
t_string	*tstr_create(void)
{
	t_string	*string;

	string = malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	tstr_init(string);
	return (string);
}

//return 0 if success, 1 - malloc error
int	tstr_clear(t_string *str)
{
	free(str->str);
	return (tstr_init(str));
}

void	tstr_free(t_string *str)
{
	free(str->str);
	free(str);
}

//return 0 if success, 1 - malloc error
int	tstr_resize(t_string *str, size_t len)
{
	char	*temp;

	while ((len + str->pos) > str->len)
		str->len <<= 1;
	temp = str->str;
	str->str = malloc(str->len + 1);
	if (!str->str)
		return (1);
	ft_memcpy(str->str, temp, str->pos + 1);
	free(temp);
	return (0);
}
