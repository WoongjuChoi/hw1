#include <stdio.h>
#include <stdlib.h>
#include <direct.h>//getcwd
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_NUM 200

void* prompt(char cBuf[]) {
	time_t rtime;
	struct tm* tminfo;
	char* uBuf = NULL;
	char dBuf[MAX_NUM];
	char* now;
	void* input;

	time(&rtime);
	tminfo = localtime(&rtime);//시간 받아오기
	now = asctime(tminfo);
	now[strlen(now) - 1] = 0;

	uBuf = getenv("USER");
	getcwd(dBuf, MAX_NUM);

	printf("[%s]%s(%s)$", now, uBuf, dBuf);

	input = fgets(cBuf, MAX_NUM, stdin);

	if (cBuf[strlen(cBuf) - 1] == '\n')
		cBuf[strlen(cBuf) - 1] = 0;
	return input;
}
int main()
{
	char cBuf[MAX_NUM];
	char* arg;
	pid_t pid;
	int status;

	pid = fork();
	printf("-------------------hw1-------------------");
	while (prompt(cBuf)) {
		if (pid == -1) {
			perror("fork error");
			return 0;
		}
		else if (pid == 0) {

			strtok(cBuf, "");
			arg = strtok(NULL, "");

			if (arg == NULL)
				execlp(cBuf, cBuf, (char*)0);
			else {
				if (strcmp(cBuf, "cd") == 0) {
					chdir(arg);
					_exit(0);
				}
				else if (strcmp(cBuf, "quit") == 0) {
					exit(0);
				}
				else
					execlp(cBuf, cBuf, arg, (char*)0);
			}
			perror("couldn't execute.");
		}
		else
			wait(0);
	}
	exit(0);
}




