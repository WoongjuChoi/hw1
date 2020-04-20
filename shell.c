#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000

int main(int argc, char**argv)
{
	char buf[MAX_LINE];
	int status;
	int pid;
	int i = 1;
	pid_t pid_child;

	printf("---Ga Young Shell---");
	while(1)
	{
		fgets(buf,MAX_LINE,stdin);
		if(strncmp(buf,"quit\n",10)==0)
		{
			break;
		}
		pid = fork();
		if(pid == -1 )
		{
			fprintf(stderr, "fork error");
			exit(0);
		}
		else if(pid == 0)//자식 프로세스
		{
			printf("I am child!\n");
			while(i < 20)
			{
				printf("child number : %d\n", i);
				i++;
				sleep(1);
			}
			execlp("/bin/ls","/bin/ls","-1",NULL);
			return 0;
			exit(0);
		}
		else // 부모 프로세스
		{
			printf("I'm parent, for waiting	for Child process\n");
			pid_child = wait(&status);
			printf("Child pid = %d\n", pid_child);
		}
	}
}
