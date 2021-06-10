#include <stdio.h>

#define RED_RIGHT 1
#define RED_LEFT 2
#define RED_DRIGHT 3
# define PIPE 4
# define OR 5
# define AND 6
# define SEMICOLON 7
# define TEXT 8
# define ENV 16
# define WILDCARD 32
# define WORD 56
# define EMPTY 0


int main (int argc, char *argv[])
{
	//for(int i = 1; i <= TEXT; i++)
	int i = 32;
		printf("i = %d res = %d\n", i, i & WORD);
   return 0;
}
