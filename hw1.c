#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
const int MAX=1024;


void run_ls(char *path){ //ls 명령어 수행
	DIR * dir=NULL;	
	struct dirent * entry=NULL;
	
	if((dir=opendir(path))==NULL){
		printf("current directory error\n");
	}
	while((entry=readdir(dir))!=NULL){
		printf("%s  ", entry->d_name);
	}
	printf("\n");
	closedir(dir);
}
int run_check(char *input){//해당 프로그램이 실행가능한지 확인
	struct stat fstat_buf;
	int ret=0;
	
	char dest[100]="/bin/";
	strcat(dest, input);
	ret=lstat(dest, &fstat_buf);
	return ret;
}

char* get_env(char *path){//경로 설정
	
	if(path==NULL)
		path=getenv("PATH");
	else
		path=getenv(path);
	printf("%s\n", path);
	return path;
}
int main(void){
	char *path;//현재 경로
	path=getcwd(NULL, MAX); //현재 디렉토리 가져오기
	
	char input[100]; //사용자 명령어
	char *ptr=(char *)malloc(100);//입력 문자열 잘라서 담아 두는 곳
	
	get_env(NULL); //환경변수

	
	while(1){
		printf("SISH  %s : ", path);
		fgets(input, 100, stdin);
		input[strlen(input)-1]='\0';

		if(strncmp(input, "quit", 4)==0){ //사용자로부터 quit입력받으면 프로그램 종료
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		
		ptr=strtok(input, " "); //개행문자 없애기	
		if(strncmp(input, "pwd", 3)==0){ //pwd명령어
			int check=run_check(input); //프로그램이 실행가능한지 확인
			if(check==0){ //실행가능하면
				printf("%s\n", path);
			}
			else{
				printf("프로그램 실행 불가\n");
			}
		}
		else if(strncmp(input, "ls", 2)==0){
			int check=run_check(input);
			if(check==0){
				run_ls(path);
			}
			else{
				printf("프로그램 실행 불가\n");
			}
		}
		else if(strncmp(input, "cd", 2)==0){
			printf("cd구간\n");
		}
	}
	
	return 0;
}
