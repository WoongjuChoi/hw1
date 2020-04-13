#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
const int MAX=1024;



int run_check(char *input){//해당 프로그램이 실행가능한지 확인
	struct stat fstat_buf;
	int ret=0;
	
	char dest[100]="/bin/";
	strcat(dest, input);
	ret=stat(dest, &fstat_buf);
	return ret;
}

char* get_env(char *path){//경로 설정
	
	if(path==NULL)
		path=getenv("PATH");
	else
		path=getenv(path);
	//printf("%s\n", path);
	return path;
}

void run_process(char *input){//프로세스 가동
	pid_t pid;
	pid=fork();
	if(pid==-1){//fork 실패
		perror("fork error");
		return;
	}
	else if(pid==0){ //자식 프로세스
		printf("*********** 자식프로세스: %d **********\n", getpid());
		printf("%s\n", input);
		exit(0);
	}
	else{
		wait(0);
	}
}
int main(void){
	char *path;//현재 경로
	path=getcwd(NULL, MAX); //현재 디렉토리 가져오기
	
	char input[100]; //사용자 명령어
	char *ptr;

	get_env(NULL); //환경변수
		
	while(1){
		printf("SISH  %s : ", path);
		fgets(input, 100, stdin);
		input[strlen(input)-1]='\0'; //fgets에 의한 개행문자 없애기	
		ptr=strtok(input, " "); // 옵션 문자 쪼개기

		if(strcmp(ptr, "quit")==0){ //사용자로부터 quit입력받으면 프로그램 종료
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		
		if(strcmp(ptr, "pwd")==0){ //pwd명령어
			int check=run_check(ptr); //프로그램이 실행가능한지 확인
			if(check==0){ //실행가능하면
				if(strtok(NULL, " ")==NULL){ //pwd 뒤에 아무것도 없으면
					printf("%s\n", path);
				}
				else{
					printf("pwd 명령어 오류\n");
				}
			}
			else{
				printf("프로그램 실행 불가\n");
			}
		}
		else if(strcmp(ptr, "ls")==0){ //ls명령
			int check=run_check(ptr);
			if(check==0){
				run_process(input);
			}
			else{
				printf("프로그램 실행 불가\n");
			}
		}
		else if(strcmp(ptr, "cd")==0){ //cd 명령
			ptr=strtok(NULL, " ");
			if(ptr==NULL){ //cd뒤에 아무것도 없으면
				chdir(get_env("HOME"));
				path=getcwd(NULL, MAX); //원래 디렉토리로
			}
			else{ //있을시 해당 경로로 이동
				char *sArr=ptr; //옵션 명령어 담기
				ptr=strtok(NULL, " ");
				if(ptr==NULL){ //경로가 정해져있다면
					if(chdir(sArr)==0){//경로 변경에 이상이 없다면
						path=getcwd(path, MAX);
					}
					else{
						printf("경로 변경 실패\n");
					}
				}
				else{
					printf("cd 명령어 오류\n");
				}
			}
		}
		else{
			printf("해당 명령어는 찾을 수 없습니다.\n");
		}
	}
	
	return 0;
}
