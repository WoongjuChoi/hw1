#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define TRUE 1
#define FALSE 0
const int MAX=1024;

int main(int argc, char *argv[]) {

    char buf[128];
    pid_t pid;
    char *path;//현재 경로
    path=getcwd(NULL, MAX); //현재 디렉토리 가져오기
    char*value;

    while(1) {
	printf("[SimpleShell] %s : ", path);
	memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf) - 1, stdin);

	if(buf[0]=='\n')	//enter처리
		continue;
	
        buf[strlen(buf) - 1] = '\0'; //개행문자없애기
        
	value = getenv(buf);
	if(value!=NULL){
		printf("%s = %s\n", buf,value);
	}	
	
	if(!strncmp(buf, "quit", strlen(buf))) {
            return -1;
        }
	
	if(!strncmp(buf, "pwd", strlen(buf))){
		printf("%s\n",path);
	}
	

        pid = fork();
        if(pid < 0) {
            perror("fork error\n");
            return -1;
        }
        else if(pid == 0) {
            execlp(buf, buf, NULL);
            exit(0);
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}
