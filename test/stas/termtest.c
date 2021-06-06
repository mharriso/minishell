#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

void gotoXY(int x, int y)
{
	static char *p;
	char   *CM;
	// if (x < 0 || y < 0 || x >= COLS || y >= LINES)
	// {
	// 	printf ("Точка (%d,%d) вне экрана\n", x, y);
	// 	return;
	// }
	CM = tgetstr("cm", &p);
	tputs(tgoto(CM, x, y), 1, putchar);
}

int main(void)
{
	int res;
	int ok;
	char *name;
	char *termtype;
	char *buffer;
	int lines;

	buffer = malloc(2048);

	// res = isatty(1);
	// printf("1 = %d\n", res);
	// name = ttyname(1);
	// printf("ttyname 1 = %s\n", name);
	// name = ttyname(0);
	// printf("ttyname 0 = %s\n", name);
	// res = ttyslot();
	// printf("ttyslot = %d\n", res);
	// name = getenv("PWD");
	// printf("PWD = %s\n", name);

	termtype = getenv("TERM");
	ok = tgetent(buffer, termtype);
	printf("ok = %d\n", ok);
	printf("buf = |%s|\n", buffer);
	lines = tgetnum("li");


	//UP = tgetstr("up",0);
	gotoXY(7, 7);
	write(1,"lines =",8);
	sleep(5);
	return (0);
}
