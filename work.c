#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>   //추가하지 않으면 cut_path = strtok(copy_path, ":"); 부터 Segmentation fault 가 발생한다.


int main(int argc, char *argv[])
{
	char input[254];	//사용자 입력을 저장하기 위한 배열 및 수정한 *argv를 저장하기 위한 배열
	char* new_argv[254];//수정한 **argv를 저장하기 위한 배열
	int new_argc;       //수정한 argc를 저장하기 위한 변수
	char* cut_path;     //PATH 경로를 parsing 하고 그 결과를 받는 포인터
	char copy_path[254];//PATH 경로를 받아오는 문자형 배열
	char new_path[254]; //PATH 경로를 수정하여 저장할 문자형 배열
	pid_t pid;          //자식프로세스의 ID 값을 저장할 변수
	char buf[255];		//현재 위치를 얻어오기 위한 문자형 배열
	new_argc = argc;    //무한 루프를 돌기 전 받아온 argc를 저장

	while (1) {		//while문 
		if (new_argc == 1) {
			getcwd(buf, 255);	//현재 위치 얻기
			printf("\033[1;33mhw1\033[0m:");				//글씨 색 추가 및 유저정보와 주소정보 표시
			printf("\033[0;34m%s\033[0m:",getenv("USER"));
			printf("\033[0;32m%s:~$\033[0m", buf);
			fgets(input, sizeof(input), stdin);		//input
			new_argv[0] = strtok(input, " ");            // input parsing
		}
		//command line 에서 아규먼트를 파싱
		for (int i = 1; ; i++) {
			if (!(new_argv[i] = strtok(NULL, " ")))
				break;
			new_argc++;
		}
		//마지막 개행문자 제거
		new_argv[new_argc - 1] = strtok(new_argv[new_argc - 1], "\n");
		//마지막 글자 뒤에 NULL 포인터 입력
		new_argv[new_argc] = (char*)NULL;
		strcpy(input, new_argv[0]);    //command를 복사
		if (strcmp(input, "quit") == 0 || strcmp(input, "QUIT") == 0) {   //프로그램 종료
			printf("프로그램이 종료됩니다. \n");
			return 0;
		}
		if (strcmp(input, "help") == 0) {
			printf("quit 또는 QUIT을 입력하면 프로그램이 종료됩니다. \n");	//도움말 
		}if (strcmp(input, "cd") == 0) {	//cd 구현
			chdir(new_argv[1]);
		}else {
			}
		//PATH파싱
		strcpy(copy_path, getenv("PATH"));
		cut_path = strtok(copy_path, ":");
		strcpy(new_path, cut_path);
		strcat(new_path, "/");
		strcat(new_path, input);//파싱한 PATH뒤에 명령어를 붙임
		strcat(new_path, "");
		pid = fork();
		if (pid == -1) {
			perror("fork error");		//포크 실패 - 프로세서 복사되지 않음
			return -1;
		}
		else if (pid == 0) {
			// child 
			//PATH가 맞을 때 까지 무한 루프, 모든 PATH 실패할 경우 탈출
			while (execv(new_path, new_argv) == -1) {
				//PATH를 파싱     
				if (!(cut_path = strtok(NULL, ":")))
					break;
				//파싱 후 PATH 뒤에 경로를 붙임
				strcpy(new_path, cut_path);
				strcat(new_path, "/");
				strcat(new_path, input);
				strcat(new_path, "");
			}
			exit(0);	//child process 종료
		}
		else {
			// parent
			wait(0);	//waiting child
		}
		//쉘로 다시 만들어주기 위해서는 다시 COMMAND LINE을 받도록 해야한다.
		new_argc = 1;
	}
	return 0;
}

