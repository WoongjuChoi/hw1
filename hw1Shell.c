#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>//fork()
#include <string.h>
#include <time.h>
#define MAX_BUF_SIZE 256

void *prompt(char cBuf[]) {//프롬포트 출력, 사용자로부터 문자열 받기
	time_t rawtime;
	struct tm *timeinfo;
	char hBuf[MAX_BUF_SIZE], uBuf[MAX_BUF_SIZE], dBuf[MAX_BUF_SIZE];
	char *now;
	void *ret;

	time(&rawtime); // 시간
	timeinfo = localtime(&rawtime); // 시간을 구조체로 변환
	now = asctime(timeinfo); // string 

	now[strlen(now) - 1] = 0; // \n 을 null character  로 변환

	gethostname(hBuf, MAX_BUF_SIZE); // save hostname to hBuf
	getlogin_r(uBuf, MAX_BUF_SIZE); // save username to uBuf
	getcwd(dBuf, MAX_BUF_SIZE); // save directoryname to dBuf

	printf("[%s]%s@%s(%s)$ ", now, hBuf, uBuf, dBuf); // print out prompt
			            
	ret = fgets(cBuf, MAX_BUF_SIZE, stdin);
	//\n을 null charactor로 변환시켜주므로 string으로 인식
	if (cBuf[strlen(cBuf) - 1] == '\n')
		cBuf[strlen(cBuf) - 1] = 0;

	return ret;
}

int main()
{
	    char cBuf[MAX_BUF_SIZE];
		pid_t pid;
		char *argument;
		int status;

	while (prompt(cBuf)) { // while successful input
						   
		if ((pid = fork()) < 0) {// pid 는 0보다 크거나 같아야한다. 아닐시:
			perror("fork error");//에러발생
		}
		else if (pid == 0) { // 자식의 경우
			strtok(cBuf, " ");
			argument = strtok(NULL, " "); // return null if no more possible seperation

									 // argument list until (char*) 0 for more than second parameter,
									 // and execute that program.
			if (argument == NULL) // no argument
				execlp(cBuf, cBuf, (char*)0);
			else { // one argument
				if (strcmp(cBuf, "cd") == 0) {
					chdir(argument);
					_exit(0);
				}
				else
					execlp(cBuf, cBuf, argument, (char*)0);
			}
			perror("couldn't execute");
		}
		waitpid(pid, &status, 0);//부모
	}

	exit(0);
}
