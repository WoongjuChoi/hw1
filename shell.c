#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void help()
{
	printf("* * * * * * * * * * * HELP* * * * * * * * * * * \n");
	printf("cd : change this directory \n");
	printf("exit : exit this shell \n");
	printf("----------------------------------\n");
}

int main()
{
	printf("help 입력\n");
	return 0;
}
