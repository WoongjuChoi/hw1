#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

char cwd[1024]; //작업 디렉토리 저장
char *stored_path[1024]; //경로 저장
char s_path[1024];
char *path_tok;


int process(char *input_str){ //실행함수
	int i = 0;
	pid_t pid;
	char *str = strtok(input_str," "); //입력 문자열 나누기
	char *tok[100];
	char *stored_str[100];
	char env[1024];
	while(tok[i] != 0){
		tok[i] = NULL;
		i++;
	}
	i = 0;
	while(str != NULL){ //char 포인터형 변수에 입력 문자열 나눈것을 대입
        tok[i] = str;
		str = strtok(NULL," "); //공백을 기준으로 나눔
		stored_str[i] = tok[i];
		i++;
	}
	
	strcpy(env,getenv("PATH")); // path값 받음
	path_tok = strtok(env,":"); //path를 :로 나눔
	sprintf(s_path,"%s%s%s",path_tok,"/",stored_str[0]); //s_path 뒤에path_tok과 /stored_str[0] (input string 자른 문자열) 붙임


	if(strcmp(stored_str[0],"cd") == 0){ //cd 입력시 비교 
		if(chdir(stored_str[1]) == 0);
		else printf("cd_failed");

	}else{
		pid = fork();
		if(pid < 0){
			perror("fork error");
			exit(0);
		}else if(pid == 0){
			while(execv(s_path,stored_str)==-1){ 
				
				if(!(path_tok=strtok(NULL,":"))){  //path_tok안의 값이 없을때 까지 반복
					break;
				}
				sprintf(s_path,"%s%s%s",path_tok,"/",stored_str[0]); //s_path에 자른 path_tok과 /stored_str[0](input string 자른 문자열) 붙임
        	    		
			}exit(0);
		}else{
			wait(0);
		}
	}
	i = 0;
	while(stored_str[i] != NULL){ //입력 문자열 저장한 변수 초기화
		stored_str[i] = NULL;
		i++;
	}
	return 0;
}


int main(){
	int i = 0;
	char str[100];
	char *tok[100];
	
	
    while(1){
		getcwd(cwd,sizeof(cwd)); //현재 디렉토리 경로
		printf("%s >>>",cwd);
		fgets(str,sizeof(str),stdin); //문자열 입력
		str[strlen(str)-1] = '\0'; //개행문자 제거
		if(strcmp(str,"quit")==0){	//quit 입력시 프로그램 종료 
            exit(0);
        }

	    process(str); // 쉘 함수 실행

	}	
	 return 0;
}
