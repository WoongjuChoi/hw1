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
	char userInput[100];

	while(1){
		scanf("%s",userInput);
		printf("%s\n",userInput);
	}

	// for (i = 0 ; i < 10 ; i++) {
	// 	pid = fork();
	// 	if (pid == -1) {
	// 		perror("fork error");
	// 		return 0;
	// 	}
	// 	else if (pid == 0) {
	// 		// child
	// 		printf("child process with pid %d (i: %d) \n", getpid(), i);
	// 		exit (0);
	// 	} else {
	// 		// parent
	// 		wait(0);
	// 	}
	// }
	return 0;
}




//TODO LIST

//1. 사용자의 입력을 받아서 단순히 출력해주는 프로그램

//2. 자식 프로세스한테 fork 해서 단순히 출력해주기.

//3. getenv key 입력이 올바르면, value출력해 주기