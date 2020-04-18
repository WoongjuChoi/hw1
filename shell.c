#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int pid;
	int status;
	int i = 1;
	pid_t pid_child;

	pid = fork();
	if( pid == -1 )
	{
		fprintf(stderr, "fork error");
		exit(0);
	}
	else if ( pid == 0 )//자식 프로세스
	{
		printf("I am child!\n");
		while(i<20)
		{
			printf("child number :%d\n", i);
			i++;
			sleep(1);
		}
		execlp("/bin/ls", "/bin/ls", "-1",NULL);
		return 0;
		exit(0);

	}
	else //부모 프로세스
	{
		printf("I'm parent, and I'm waiting for Child proces\n");
		pid_child = wait(&status);
		printf("Child pid = %d\n", pid_child);
	}
	printf("---The end---\n");
	return 0;

}
