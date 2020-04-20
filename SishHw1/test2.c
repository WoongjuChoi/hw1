#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if(argc == 1)
	{
		printf("Usage: %s <exec path> , [arg0, arg1, arg2, ...]\n", argv[0]);
		return 1;
	}

	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		return 1;
	}
	else if(pid == 0)
	{
		wait(0);
	}
	else
	{
		execv("./test", argv+1);
		return 0;
	}
	return 0;
}

