#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
const int MAX=1024;

int main(/*int argc, char *argv[]*/) {

    char buf[256];
    char*value;
    char *path;//현재 경로
    path=getcwd(NULL, MAX); //현재 디렉토리 가져오기
    char *ret_ptr;
    char *next_ptr;
    int argv;
    char *arg[MAX];
    static const char delim[] = " \t\n"; //공백,탭,개행으로 구분
    pid_t pid;

    while(1) {

	printf("[SimpleShell] %s : ", path);
	memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf) - 1, stdin);
	argv=0;
	
       	ret_ptr = strtok_r(buf, delim, &next_ptr);

	while(ret_ptr){
		arg[argv++]=ret_ptr;
		ret_ptr=strtok_r(NULL,delim,&next_ptr);
	}
	arg[argv] = (char*)0;

	if(buf[0]=='\n')	//enter처리
		continue;
	

	//PATH, USER, time, ...
	value = getenv(buf);
	if(value!=NULL){
		printf("%s = %s\n", buf,value);
	}	

	//quit
	if(!strcmp(arg[0], "quit")) {
            return -1;
        }
	

	*/
	//cd
	if(!strcmp(arg[0],"cd")){
		if(arg[1]!=NULL){
			path = arg[1];	//인자가 있는경우
		}
		else if((path = (char*)getenv("HOME")) ==NULL){
			path = getcwd(NULL,MAX);	//인자가 없는 경우 HOME
		}
		path=getcwd(path,MAX);
		if(chdir(path) == -1){
			fprintf(stderr,"%s: wrong directory\n",path);
		}
	}
	*/
	
	//fork
	if ((pid=fork()) == -1) {
		perror("fork error");
		return 0;
	}
	else if (pid != 0) {
		// Parent: waiting for child quit
		wait(0);
	} else {
		// Child
		execvp(arg[0],arg);
                exit (0);
	}
    }

    return 0;
}
