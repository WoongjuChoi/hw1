
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define MAX 200

char c_time() { // 현재 시간 나타내는 함수

	time_t ct;
	struct tm tm; // 초, 분, 시 등 정의되어있는 구조체
	ct = time(NULL);
	tm = *localtime(&ct); // strct tm 구조체 반환
	return printf("<%d-%d-%d %d:%d:%d> ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	//시간 출력 return
}

void setting_path(char work_path[MAX], char* save_path, char save_cmd[MAX])
{
	strcpy(work_path, save_path); //토큰 분리 작업한 것을 work_path에 복사
	strcat(work_path, "/");              
	strcat(work_path, save_cmd); // /명령어 를 work_path 뒤에 붙임
	strcat(work_path, "");
}

int main(int argc, char** argv) {
	int i = 0;

	char* ptr_cmd[MAX];        //명령어 복사 포인터
	char cmd[MAX];             //명령어 수정하여 보관하는 배열
	char save_cmd[MAX];         //명령어를 보관할 배열

	char path[100];				//현재위치 배열
	char* save_path;             //PATH 작업완료한 배열 포인터
	char set_path[MAX];        //PATH를 복사하고 저장하는 배열
	char work_path[MAX];         //PATH 작업하는 배열

	pid_t pid; 


	while (1) {

		c_time(); // 현재시간 표시
		getcwd(path, 100);
		printf("%s$ ", path); //현재 위치 출력
		fgets(cmd, sizeof(cmd), stdin);  //명령어 입력

		if (cmd[0] == '\n') //엔터 입력시 다시 입력받도록 함
			continue;

		ptr_cmd[0] = strtok(cmd, " ");   //스페이스바 구분으로 명령어 나누기

		int i = 1;
		while (ptr_cmd[i] = strtok(NULL, " ")) { //argument 더하기
			i++;
			argc++;
		}

		ptr_cmd[argc - 1] = strtok(ptr_cmd[argc - 1], "\n"); //명령어 개행문자 제거
		strcpy(save_cmd, ptr_cmd[0]);       // " "전을 문자열에 복사

		if (strcmp(save_cmd, "quit") == 0)   //quit 입력시 프로그램 종료
			return 0;

		else if (strcmp(save_cmd, "cd") == 0) { //cd:change directory
			if (ptr_cmd[1] == NULL) { //cd 뒤에 아무입력 없을시 입력 없다고 출력
				printf("There is no directory input\n");
			}
			else { //cd 뒤 디렉토리로 변경, 변경 후 디렉토리 출력
				chdir(ptr_cmd[1]);
				getcwd(path, 100);
				printf("current directory : %s\n", path);
			}
		}

	
		strcpy(set_path, getenv("PATH"));  //현재경로 받기
		save_path = strtok(set_path, ":");  // ':' 으로 토큰 분리
		setting_path(work_path, save_path, save_cmd);
		

		pid = fork(); //자식프로세스 생성

		if (pid == -1) {
			printf("fork error \n");
			return -1;
		}

		if (pid == 0) {  //자식프로세스
			while (execv(work_path, ptr_cmd) == -1) { //exec 함수 사용
				if (!(save_path = strtok(NULL, ":")))
					break;
				setting_path(work_path, save_path, save_cmd);

			}
			exit(0);
		}

		else {
			wait(0);
		}
		argc = 1; //초기화
	}
}


