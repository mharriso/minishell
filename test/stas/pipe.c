#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

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

typedef struct	s_fdi
{
	int		fd[2];
	int		type;
}				t_fdi;

typedef struct	s_fork
{
	pid_t	pid;
	t_fdi	fd[2];
	int		size;
}				t_fork;


void ft_dup(t_fdi *info, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dup2(info->fd[info->type], info->type);
		close(info->fd[0]);
		close(info->fd[1]);
		info++;
	}
}

void ft_do_fork(t_fork *info, char *path, char **argv, char **env)
{
	info->pid = fork();
	if (!info->pid)
	{
		ft_dup(info->fd, info->size);
		execve(path, argv, env);
	}
}

void	ft_pipe()
{

}

int main (int argc, char **argv, char **env)
{
	pid_t pid;
	pid_t pid2;
	int fd[2];

	int status;

	char **a;
	a = (char**)malloc(sizeof(char*) * 2);
	a[0] = strdup("cat");
	a[1] = NULL;
	char **b;
	b = (char**)malloc(sizeof(char*) * 2);
	b[0] = strdup("ls");
	b[1] = NULL;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);

		int ffd;
		int ffd1;

		ffd = open("a", O_CREAT | O_WRONLY | O_APPEND, S_IREAD | S_IWRITE);
		dup2(ffd, 1);

		ffd1 = open("b", O_CREAT | O_WRONLY | O_APPEND, S_IREAD | S_IWRITE);
		dup2(ffd1, 1);

		execve("/bin/ls", b, env);
	}

	pid2 = fork();
	//printf("pid = %d\n", pid2);
	if (!pid2)
	{
		dup2(fd[0],0);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/cat", a, env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	printf("\npid %d\n", WTERMSIG(status));
	waitpid(pid2, &status, 0);
	printf("pid2 %d\n", WTERMSIG(status));

	return (0);
}
