#include <stdio.h>

static int wc_check(const char *wc, const char *str)
{
	int res;

	res = 0;
	while(*wc == *str && *wc)
	{
		wc++;
		str++;
	}
	if (!*wc && !*str)
		res++;
	else if (*wc == '*')
	{
		wc++;
		while (*str)
		{
			if (*wc == *str)
				res += wc_check(wc, str);
			str++;
		}
		res += wc_check(wc, str);
	}
	return (res);
}

int main(int argc, char **argv)
{
	int res;

	if (argc == 2)
	{
		res = wc_check("*.c", argv[1]);
		printf("res = %d\n", res);
	}
	return (0);
}
