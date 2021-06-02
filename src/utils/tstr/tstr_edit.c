#include "tstr.h"

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
char	*tstr_insert_size(t_string *str, size_t pos,
							const char *src, size_t size)
{
	char	*str_end;
	size_t	len;

	if (pos == str->pos)
	{
		if (tstr_add_size(str, src, size))
			return (NULL);
		return (&((str->str)[pos]));
	}
	len = ft_strlen(str->str);
	if ((len + size) > str->len)
		if (tstr_resize(str, size))
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
	ft_memcpy(&((str->str)[pos - 1]), &((str->str)[pos]), len);
}
