#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX 256
void tockenize(char*);
void cd(char*);
int argv;
char *ret_ptr;
char *next_ptr;
char *arg[MAX];
int main() {
    char buf[MAX];
    char*value;
    pid_t pid;

    while(1) {

	printf("[SimpleShell] %s : ", getcwd(NULL,MAX));
	memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf) - 1, stdin);

	if(buf[0]=='\n')	//enter처리
		continue;

	tockenize(buf);

	//PATH, USER, time, ...
	value = getenv(buf);
	if(value!=NULL){
		printf("%s = %s\n", buf,value);
	}	

	//quit
	if(!strcmp(arg[0], "quit")) {
            return -1;
        }
	
	//cd
	else if(!strcmp(arg[0],"cd")){
		cd(arg[1]);
	}
	
	//fork
	if ((pid=fork()) == -1) {
		perror("fork error");
		return 0;
	}
	else if (pid != 0) {	// Parent: waiting for child quit
		wait(0);
	} else {		// Child
		execvp(arg[0],arg);
                exit (0);
	}
    }

    return 0;
}

void tockenize(char buf[MAX]){
	static const char delim[] = " \t\n";
	argv = 0;
	ret_ptr = strtok_r(buf, delim, &next_ptr);
	while(ret_ptr) {
		arg[argv++] = ret_ptr;
		ret_ptr = strtok_r(NULL, delim, &next_ptr);
	}
	arg[argv] = (char*)0;
}

void cd(char* target){
	char name[MAX];
	if(chdir(target) == -1) {
		chdir(getenv("HOME"));
	}
	getcwd(name,MAX);
	printf("%s\n",name);
	if(setenv("PWD",name,1)==-1)
		printf("fail");
}
