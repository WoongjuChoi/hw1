#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

#define max 255

void *prompt(char cBuf[]) {
	time_t rawtime;
	struct tm *timeinfo;
	char hBuf[max], uBuf[max], dBuf[max];
	char *now;
	void *ret;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	now = asctime(timeinfo);

	now[strlen(now)-1] = 0;

	gethostname(hBuf, max);
	getlogin_r(uBuf, max);
	getcwd(dBuf, max);

	printf("[%s]%s@%s(%s)$ ", now, hBuf, uBuf, dBuf);

	ret = fgets(cBuf, max, stdin);

	if(cBuf[strlen(cBuf)-1] == '\n')

		cBuf[strlen(cBuf)-1] = 0;
	return ret;
}
			

int main(void) {
	char cBuf[max];
	char *arg;
	pid_t pid;
	int status;
	while(prompt(cBuf)) {
		if((pid = fork()) < 0) {
			perror("FORK ERROR");
		}
		else if(pid == 0) {
			strtok(cBuf, " ");
			arg = strtok(NULL, " ");
	
			if(arg == NULL)
				execlp(cBuf, cBuf, (char*) 0);
			else {
				if(strcmp(cBuf, "cd") == 0) {
					chdir(arg);
					_exit(0);
				}
				else
					execlp(cBuf, cBuf, arg, (char*) 0);
			}
			perror("could not execute");
		}
		waitpid(pid, &status, 0);
	}
	exit(0);
}
