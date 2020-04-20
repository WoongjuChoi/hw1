#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 256

int main(int argc, char *argv[]){ 
    char command[SIZE]; //명령어를 입력받을 배열
    char* new_command[SIZE]; //명령어를 받아 token으로 명령 부분만 가져오기 위한 배열 
    int new_argc;
    pid_t pid; // 프로세스 ID
    char path[SIZE]; // path를 저장하여 execv에 사용
    int i=0; // 반복문 사용시 사용
    char delimeter[10] = " :";
    char *new_path;
    char new_pathArray[SIZE];
  

    new_argc=argc;
    while(1) {
        
        printf("MyminiShell$ "); //데코레이션
        fgets(command, sizeof(command) - 1, stdin); // 입력을 받는다.
        new_command[0] = strtok(command,delimeter);
      for(int i=1; ;i++){
      if(!(new_command[i]=strtok(NULL,delimeter)))
      break;
      new_argc++;  // 최초 1값을 가지고 있음.
}

        new_command[(new_argc) - 1] = strtok(new_command[new_argc-1],"\n");  // 개행문자 제거
        new_command[(new_argc)]=(char*) NULL;
        strcpy(command,new_command[0]);
        if(!strncmp(command, "quit", strlen(command))) { // quit입력 시 종료
            printf("quit the shell\n");
            break;
        }

  strcpy(path,getenv("PATH"));  // path값을 받는다
  new_path = strtok(path, delimeter); //new_path를 이용해서 path를 :로 나눈다.
  strcpy(new_pathArray,new_path); // new_pathArray에 strtok된 문자열을 삽입하고 각 뒤에 /command를 붙인다.
  strcat(new_pathArray, "/");
  strcat(new_pathArray, command);
  


        pid = fork();
        if(pid < 0) {
            perror("fork error\n");
            break;
        }
        else if(pid == 0) { // 자식 프로세스

while(execv(new_pathArray,new_command)==-1){

if(!(new_path=strtok(NULL,delimeter))) // new_path값이 다 떨어질때까지 반복
break;

strcpy(new_pathArray,new_path);
strcat(new_pathArray, "/");
strcat(new_pathArray, command);


}
exit(0);
}
        else { //부모프로세스
            wait(0);
        }
new_argc=1;
    }

}

	




