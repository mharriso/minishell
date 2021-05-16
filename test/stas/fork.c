#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main ()
{
pid_t pid;
pid_t wait_pid;
int stat;

stat = 0;
wait_pid = 0;
pid = getpid();
printf("main pid = %d\n", pid);
pid = fork();
if (pid)
	wait_pid = pid;

pid = fork();
if (!pid)
	wait_pid = 0;
else if (pid && !wait_pid)
	wait_pid = pid;

if (wait_pid)
{
	wait_pid = waitpid(wait_pid ,&stat, 0);
	if (WIFEXITED(stat))
	{
		pid = getpid();
		printf("chl %d is done, my pid = %d\n", wait_pid, pid);
	}
}
pid = getpid();
printf("pid %d is done\n", pid);
return EXIT_SUCCESS;
}
