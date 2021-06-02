#include <stdlib.h>
#include "history.h"
#include "libft.h"

static char	*get_path_to_ms(const char *str)
{
	char		*last;
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
	last = ft_strrchr(str, '/');
	if (!last)
		return (NULL);
	len = last - str + 1;
	last = malloc(len + 1);
	ft_memcpy(last, str, len);
	return (last);
}

static char	*get_abs_path(const char *pname)
{
	char	*path;
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 512);
	temp = ft_strjoin(pwd, "/");
	free(pwd);
	pwd = get_path_to_ms(pname);
	if (pwd)
	{
		path = ft_strjoin(temp, pwd);
		free(pwd);
		free(temp);
	}
	else
		path = temp;
	return (path);
}

char	*history_get_fname(char term_num, const char *pname)
{
	char	*str;
	char	*temp;

	str = get_abs_path(pname);
	temp = ft_strjoin(str, HISTORY_FNAME);
	free(str);
	str = ft_strjoin(temp, &term_num);
	free(temp);
	return (str);
}
