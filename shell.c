#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//변수 선언부
	char str[255]; //사용자 입력을 저장할 변수
	char buf[255]; 
	char *tok[100];
	
	getcwd(buf, 255);
	//printf("%s:", buf);
	fgets(str, 255, stdin);
	//printf("%s", str);
	
	pid_t cpid;
	cpid = fork();
	
	// Fork Error!
	if(cpid == -1){
		perror("fork error");
		return 0;
	}

	// Fork 실행시
	
	//Child 프로세스 실행 
       	else if (cpid == 0) {

		//ls 명령어 실행
		if(strcmp(str, "ls\n") == 0) 
			execlp("/bin/ls", "/bin/ls",  NULL);
		
		//pwd 명령어 실행
		if(strcmp(str, "pwd\n") == 0)
			execlp("/bin/pwd", "/bin/pwd", NULL);
		
		//cd 명령어 실행
		if(strcmp(str, "cd\n") == 0){
			execlp("/bin/cd", "/bin/cd", NULL);
			printf("홈디렉토리로 이동");
		}
		
		//quit 명령어 실행
		if(strcmp(str, "quit\n") == 0) {
			printf("shell을 종료합니다.");		
		}
		
		//child process 실행 및 id 출력
		printf("child process, pid: %d\n", getpid());
		exit(0);		
	}
	
	// Parent process 실행
	else {
		wait(0);
	}

	return 0;

}
