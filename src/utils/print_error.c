#include <stdio.h>
#include "libft.h"

void	print_error(const char *name, const char *msg)
{
	char	*str;
	char	*temp;
	int		len;

	temp = ft_strjoin("minishell: ", name);
	str = ft_strjoin(temp, msg);
	len = ft_strlen(str);
	write(2, str, len);
	free(temp);
	free(str);
}
