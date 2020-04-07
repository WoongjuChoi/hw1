#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int i;

	for (i = 0 ; i < 10 ; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork error");
			return 0;
		}
		else if (pid == 0) {
			// child
			i = i+2;
			printf("child process with pid %d (i: %d) \n", getpid(), i);
			exit (0);
		} else {
			// parent
			i++;
			printf("parent process with pid %d (i : %d) \n", getpid(), i);
			wait(0);
		}
	}
	return 0;
}

