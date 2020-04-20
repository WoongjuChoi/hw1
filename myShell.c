#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

void path_parsing(char r_path[MAX], char* c_path, char cmd[MAX])
{
	strcpy(r_path, c_path);
	strcat(r_path, "/");
	strcat(r_path, cmd);
	strcat(r_path, "");

}//path 파싱

int main(int argc, char** argv) {

	char* ncBuf[MAX];
	char cBuf[MAX];    
	int n_cBuf;

	char* m_path;
	char s_path[MAX];
	char r_path[MAX];

	pid_t pid;          //자식프로세스

	char cmd[100];

	int i;		

	n_cBuf = argc;

	//프롬프트
	char* uBuf = NULL; //사용자
	char dBuf[MAX]; //dir 위치
	//시간
	time_t ctime;
	struct tm* tm_info;
	char* now;

	while (1) {

		time(&ctime);
		tm_info = localtime(&ctime);//시간 받아오기
		now = asctime(tm_info);
		now[strlen(now) - 1] = 0;

		uBuf = getenv("USER");

		getcwd(dBuf, MAX);

		printf("[%s]%s(%s)$", now, uBuf, dBuf);

		if (n_cBuf == 1) {
			fgets(cBuf, sizeof(cBuf), stdin);  //명령어 입력
			ncBuf[0] = strtok(cBuf, " ");		//명령어 나누기
			//argument 더하기
			for (i = 1; ; i++) {
				ncBuf[i] = strtok(NULL, " ");
				if (!(ncBuf[i]))
					break;
				n_cBuf++;
			}

			ncBuf[n_cBuf - 1] = strtok(ncBuf[n_cBuf - 1], "\n");//\n 제거
		
			strcpy(cmd, ncBuf[0]);    //명령어 복사
			if (strcmp(cmd, "quit") == 0) //quit입력
			{
				printf("----ended----\n");
				return 0;
			}
			else if (strcmp(cmd, "cd") == 0) {//cd입력
				if (ncBuf[1] == NULL) {
					printf("no input");
				}
				else {
					chdir(ncBuf[1]);
					getcwd(dBuf, MAX);
					printf("cd : %s\n", dBuf);
				}
				
			}
		}
		//path 파싱
		strcpy(s_path, getenv("PATH"));
		m_path = strtok(s_path, ":");		//':'로 분리
		path_parsing(r_path, m_path, cmd);
		
		pid = fork();//자식 프로세스 생성

		if (pid == -1) {
			printf("fork error \n");
			return -1;
		}
		//자식 프로세스
		if (pid == 0) {
			//path가 맞을 때 까지 무한 루프, 모든 path실패할 경우 탈출
			while (execv(r_path, ncBuf) == -1) {		
				if (!(m_path=strtok(NULL,":")))					
					break;
				path_parsing(r_path, m_path, cmd);

			}
			exit(0);
		}
		wait(0);

		n_cBuf = 1;//값 초기화

	}
}
