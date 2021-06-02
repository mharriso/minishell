#include <unistd.h>

int	term_putchar(int c)
{
	int	res;

	res = write(1, &c, 1);
	return (res);
}

void	term_clear_str(char *str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
}

int	term_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		res;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == '[' && s2[i] == 'O')
		{
			i++;
			continue ;
		}
		if (s1[i] != s2[i])
		{
			res = s1[i] - s2[i];
			return (res);
		}
		i++;
	}
	return (0);
}
