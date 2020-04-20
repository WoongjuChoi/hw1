#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

char* tokens[256];


int main(){
	char input[1024];
	char* tokens[256];
	int num;
	char AllPath[1024];
	char* modified_path;
	char find_path[1024];
	pid_t pid;
	
	printf("enter quit to exit\n");
	while(1){
	printf("SISH 2020OS %s@%s: ",getenv("USER"),getenv("PWD"));
	fgets(input,30,stdin);//사용자입력
	if(strcmp(input,"\n")==0) continue;
	if(strcmp(input,"quit\n")==0){printf("quit exit\n");exit(0);}
	
	num=0;
	tokens[num]=strtok(input," \n");//input을띄어쓰기 기준으로  토큰으로 나눈다
	while(1){
	if(tokens[num] == NULL) break;//토큰이 null이면 탈출
	printf("tokens[%d]=%s\n",num,tokens[num]);
	num++;
	tokens[num]=strtok(NULL," \n");//다음 토큰 정하기
	}
	if(strcmp(tokens[0],"cd")==0){}//cd dir 입력받기

	strcpy(AllPath,getenv("PATH"));//모든 경로 얻기
	modified_path=strtok(AllPath,":");//경로를 :기준으로 나눈다. 첫번째 조각은 modified_path
	sprintf(find_path,"%s%s%s",modified_path,"/",tokens[0]);//find_path=mo_path+/+토큰

	pid=fork();
	if(pid==-1){printf("error");exit(1);}
	else if (pid==0){
		while(1){//반복
			if(execve(find_path,tokens,NULL) !=-1){printf("path:%s",find_path);break;}//실행되는 경로를 찾으면 나가기
			modified_path=strtok(NULL,":");//:기준 다음 조각이 mo_path
			if(modified_path==NULL){printf("no file or directory\n");break;}//path를 다 찾아도 없는경우
			sprintf(find_path,"%s%s%s",modified_path,"/",tokens[0]);//find_path=mo_path+/+토큰
			
		}exit(1);
	}
	else{wait(&pid);}
	}
	return 0;

}


