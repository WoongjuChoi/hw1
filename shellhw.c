#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
        while(1){
		pid_t pid;
		pid=fork();
		if(pid==-1){
			perror("fork error");
			return 0;
		}
		else if(pid == 0){
			char *argv[2];
			argv[0]="/bin/sh";
			argv[1]=NULL;
                        execve(argv[0],argv,NULL);
			printf("d\n");
			exit(0);
		}
		else {
			wait(0);
		}
	}
	return 0;
}
