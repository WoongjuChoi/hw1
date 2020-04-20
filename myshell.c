#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
char cwd[1024]; //실시간을 변경되는 현재 디렉터리 저장
char cwd_init[1024]; // 초기 디렉터리 > 자식 파일
char CHILD_PATH[1024];
//명령어를 파싱한다 -> new_argv 문자열 배열(1번부터)에 각각 담는다. (뛰어쓰기,개행,,,탭 구분)
void InputParsing(char *command, char **new_argv)
{
    int j;
    char *str, *next_ptr;
    for (int i = 0; i < 100; i++){
        new_argv[i] = NULL;
    }
    for (j = 1, str = command;; str = NULL, j++){
        new_argv[j] = strtok_r(str," ,\t\n", &next_ptr);
        if (new_argv[j] == NULL || strcmp(new_argv[j],"\n")==0)
            break;
    }
    return;
}
void init(){
	getcwd(cwd_init, sizeof(cwd_init));
	strcpy(CHILD_PATH,cwd_init);
	strcat(CHILD_PATH,"/child");
	return;
}


int main(int argc, char *argv[])
{
	puts("myshell powered by DOSIMPACT");
	init();
	pid_t pid;
	int i;
	char userInput[100];
	//----------------------------------------------
	char* saveptr;
    char* new_argv[100] = {
        NULL,
    };
	char* username = getenv("USER");
	
	while(1){
		//char* pwd = getenv("PWD");
		getcwd(cwd, sizeof(cwd));
		printf("✅myshell:%s:%s#",username,cwd);
		fgets(userInput,sizeof(userInput),stdin);
		
		if(strcmp(userInput,"quit\n")==0){
			puts("MY SHELL EXIT THANKS..❤");
			break;
		}
		if(strcmp(userInput,"\n")==0){
			continue;
		}


		InputParsing(userInput, new_argv);
		new_argv[0] = argv[0];
		if(strcmp(new_argv[1],"cd")==0){
			chdir(new_argv[2]) == 0;
			continue;
		}
		pid = fork();
		if(pid == -1){
			perror("ERROR: fork fail");
		}
		else if(pid == 0){
			// char resolved_path[1000];
			// realpath(argv[0], resolved_path);
			// printf("real path %s",resolved_path);
			execve(CHILD_PATH,new_argv,environ);
			exit(0);
		}else{
			wait(0);
		}
		
	}

	return 0;
}


//TODO LIST

//1. 사용자의 입력을 받아서 단순히 출력해주는 프로그램 ✅

//2. 자식 프로세스한테 fork 해서 단순히 출력해주기. ✅

//2. 자식 프로세스에서, exec사용해, 단순이 인자값 출력하는 프로그램 ✅

//3. getenv key 입력이 올바르면, value출력해 주기 ✅