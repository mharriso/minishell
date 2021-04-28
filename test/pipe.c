#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void read_from_pipe (int file)
{
        FILE *stream;
        int c;
        stream = fdopen (file, "r");
        while ((c = fgetc (stream)) != '!')
                putchar (c);
        fclose (stream);
}
        /* Пишем некоторый произвольный текст в канал. */
void write_to_pipe (int file)
{
        FILE *stream;
        stream = fdopen (file, "w");
        fprintf (stream, "hello, world\n");
        fprintf (stream, "goodbye, world!\n");
        fclose (stream);
}

void kill_second(int pid)
{
	printf("second_kill\n");
	//kill(pid, SIGKILL);
}

int main (int argc, char **argv, char **env)
{
	pid_t pid;
	int fd[2];

	int *st;

	char **a;
	a = (char**)malloc(sizeof(char*) * 2);
	a[0] = strdup("yes");
	a[1] = NULL;
	char **b;
	b = (char**)malloc(sizeof(char*) * 2);
	b[0] = strdup("head");
	b[1] = NULL;

	pid = fork();
	if (!pid)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			close(0);
			dup2(fd[0], 0);
			execve("/usr/bin/head", b, env);

		}
		else
		{
			close(1);
			dup2(fd[1],1);
			execve("/usr/bin/yes", a, env);
		}
	}
	//sleep(1);
	//kill(pid, SIGKILL);
	pid = getpid();
	printf("pid = %d\n", pid);
	return (0);
}
