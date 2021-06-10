#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//SIGINT = ctrl+c;
//SIGQUIT = ctrl+\;
// = ctrl+d;

void	handle_c(int p)
{
	printf("ctrl+c\n");
}
void	handle_d(int p)
{
	printf("ctrl+d\n");
}
void	handle_backslash(int p)
{
	printf("ctrl+backslash\n");
}

int	main(void)
{
	signal(SIGINT, handle_c);
	// signal(SIGQUIT, handle_backslash);
	// signal(SIGTSTP, handle_d);
	// sleep(15);
	return (0);
}
