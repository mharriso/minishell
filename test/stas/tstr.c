#include <stdlib.h>
#include "libft.h"

#include <stdio.h>

typedef struct	s_string
{
	char	*str;
	size_t	len;
	size_t	pos;
}				t_string;

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
t_string	*tstr_create()
{
	t_string	*string;

	string = malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	if (tstr_init(string))
		return (NULL);
	return (string);
}

//return 0 if success, 1 - malloc error
int	tstr_clear(t_string *str)
{
	free(str->str);
	return (tstr_init(str));
}

void tstr_free(t_string *str)
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


//return 0 if success, 1 - malloc error
int	tstr_add_size(t_string *str, const char *src, size_t len)
{
	char	*temp;

	if ((len + str->pos) > str->len)
	{
		if (tstr_resize(str, len))
			return (1);
	}
	ft_strlcat(str->str, src, len + str->pos + 1);
	str->pos += len;
	return (0);
}

//return 0 if success, 1 - malloc error
int	tstr_add(t_string *str, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	return (tstr_add_size(str, src, len));
}

//return pointer to str at the start of src, NULL - malloc error
char*	tstr_insert_size(t_string *str, size_t pos, const char *src, size_t size)
{
	char *str_end;
	size_t len;

	if (pos == str->pos)
	{
		if (tstr_add_size(str, src, size))
			return (NULL);
		return (&((str->str)[pos]));
	}
	len = ft_strlen(str->str);
	if ((len + size) > str->len)
		if(tstr_resize(str, size))
			return (NULL);
	while (len >= pos)
	{
		(str->str)[len + size] = (str->str)[len];
		if (len == 0)
			break ;
		len--;
	}
	ft_memcpy(&((str->str)[pos]), src, size);
	str->pos += size;
	return (&((str->str)[pos]));
}

void	tstr_remove(t_string *str)
{
	if (str->pos < 1)
		return ;
	str->pos--;
	str->str[str->pos] = '\0';
}

void	tstr_remove_at(t_string *str, size_t pos)
{
	size_t	len;

	if (pos == str->pos)
	{
		tstr_remove(str);
		return ;
	}
	len = ft_strlen(&((str->str)[pos - 1]));
	str->pos--;
	ft_memcpy(&((str->str)[pos - 1]),&((str->str)[pos]), len);
}

///////// CHECK

// void	tstr_add_size(t_string *str, const char *src, size_t len)
// {
// 	char	*temp;

// 	if ((len + str->pos) > str->len)
// 		tstr_resize(str, len);
// 	ft_strlcat(str->str, src, len + str->pos + 1);
// 	str->pos += len;
// }

// void	tstr_add(t_string *str, const char *src)
// {
// 	size_t	len;

// 	len = ft_strlen(src);
// 	tstr_add_size(str, src, len);
// }

// //return pointer to str at the start of src
// char*	tstr_insert_size(t_string *str, size_t pos, const char *src, size_t size)
// {
// 	char *str_end;
// 	size_t len;

// 	if (pos == str->pos)
// 	{
// 		tstr_add_size(str, src, size);
// 		return (NULL);
// 	}
// 	len = ft_strlen(str->str);
// 	if ((len + size) > str->len)
// 		tstr_resize(str, size);
// 	while (len >= pos)
// 	{
// 		(str->str)[len + size] = (str->str)[len];
// 		if (len == 0)
// 			break ;
// 		len--;
// 	}
// 	ft_memcpy(&((str->str)[pos]), src, size);
// 	str->pos += size;
// 	return (&((str->str)[pos]));
// }

// void	tstr_insert(t_string *str, size_t pos, const char *src)
// {
// 	size_t	len;

// 	len = ft_strlen(src);
// 	tstr_insert_size(str, pos, src, len);
// }

int	main()
{
	t_string *str;

	str = tstr_create();

	tstr_add(str, "Heallo! sdf");
	printf("|%s|\n", str->str);
	tstr_remove_at(str, 2);
	printf("|%s|\n", str->str);
	tstr_remove(str);
	printf("|%s|\n", str->str);
	tstr_remove(str);
	printf("|%s|\n", str->str);
	tstr_remove(str);
	printf("|%s|\n", str->str);
	tstr_remove(str);
	printf("|%s|\n", str->str);
	tstr_insert_size(str, 5, " World", 6);

	printf("|%s|\n", str->str);

	tstr_clear(str);
	tstr_free(str);
	return (0);
}
