#include <stdlib.h>
#include "libft.h"

char	*get_path_to_ms(const char *str)
{
	char		*path;
	size_t		len;

	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '.')
	{
		str++;
		if (*str == '/')
			str++;
	}
	path = ft_strrchr(str, '/');
	if (!path)
		return (NULL);
	len = path - str + 1;
	path = malloc(len + 1);
	ft_memcpy(path, str, len);
	return (path);
}
