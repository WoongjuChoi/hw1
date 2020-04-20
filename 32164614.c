#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_B 1024

int cd(char *path){
	return chdir(path);
}

void PATH_DES(char *real_path, char* modified_path, char cmd[MAX_B]) {
	strcat(real_path, "/bin");
	strcat(real_path, "/");
	strcat(real_path, cmd);
}
//void 함수에서 작동하면 메모리 문제를 일으키는 거 같아서 main 함수로 옮김
int main(void)
{	
	printf("Own shell (if you want to exit your shell, enter -quitkey-i\n");
	while (1) {
		char FKRUN[MAX_B];
    int stat_loc;
    char cmd[254]="\0";
    char *p;
    char* get_order[MAX_B]; //수정한 argument vector를 저장하기위한 배열
    char order[MAX_B]; //수정한 argument vector를 저장하기위한 변수
    char* modified_path="/bin/";

    char copy_path[MAX_B];
    char real_path[MAX_B] = "";
    int new_argc = 0;
    //int cmd_argu;
    //new_argc = argc;
    char *temp_str;
    char *alt = FKRUN; //strtok 함수 사용시 자를 문자열을 복사해 주어야 함
    pid_t child_pcs;
    char *ptr; //자를 문자열을 임시로 보관할 장소
    /*
    if (new_argc == 1) {
      fgets(order, sizeof(order), stdin);
      get_order[0] = strtok(order, "\t\n");
    }
    */
    fgets(FKRUN, MAX_B, stdin);
		p = strchr(FKRUN, '\n');
		if(p) *p=0;
    ptr = strtok_r(alt, " ", &temp_str);

    while (ptr) {
      get_order[new_argc] = ptr;
      new_argc++;
      ptr = strtok_r(NULL, " ", &temp_str);
    }
    

    //get_order[new_argc - 1] = strtok(get_order[new_argc - 1], "\n");
    get_order[new_argc] = NULL;
    strcat(cmd, get_order[0]);

    if (strcmp(cmd, "quit") == 0) {
      printf("quit!!\n");
      break;
    }
    if(strcmp("cd", get_order[0]) == 0) { 
			if(cd(get_order[1]) < 0) {
				perror(get_order[1]);
			}
			continue;
		}


    //strcpy(copy_path, getenv("PATH"));
    //modified_path = "/bin";
    //strtok(copy_path, ":");
    PATH_DES(real_path, modified_path, cmd);
    child_pcs = fork();
    if (child_pcs == -1)
    {
      perror("fork error\n");
      exit(0);
    }
    else if (child_pcs == 0)
    {
      if (execv(real_path, get_order) == -1) {
        /*
        if (!(modified_path = strtok(NULL, ":")))
          break;
        PATH_DES(real_path, modified_path, cmd);
        */
        perror("FAILED\n");
        exit(0);
      } // child process를 종료
    }
    else{
      wait(&stat_loc);
    }
      //new_argc = 1; 
  }
	return 0;
} 
