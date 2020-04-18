#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char** argv) {

	char* new_argv[1024];//수정한 **argv를 저장하기 위한 배열
	char _argv[1024];    //수정한 *argv를 저장하기 위한 배열
	int new_argc;       //쉘로 작동을 위한 임의의변수, 수정한 argc를 저장하기 위한 변수

	char* modified_path;
	char copy_path[1024];
	char real_path[1024];
	pid_t pid;          //자식프로세스의 ID 값을 저장할 변수

	char command[100];

	int i;		//command line에서 argument부분 파싱할때 쓰는 변수이다.

	new_argc = argc;    //while문을 돌기 전 받아온 argc를 저장

	//prompt관련 변수들
	char pwd_buf[100]; //pwd
	time_t now_time;
	struct tm *now_date;
	char time_buf[100];

	while (1) {
		//쉘로 작동함
		
		getcwd(pwd_buf, 100);	//strcpy(pwd_buf, getenv("PWD")); 안되는 이유 모르겠음
		
		time(&now_time);
		now_date = localtime(&now_time);
		strcpy(time_buf, asctime(now_date));
		printf("<PWD:%s><USER:%s><TIME:%s>", pwd_buf, getenv("USER"), time_buf);

		if (new_argc == 1) {
			fgets(_argv, sizeof(_argv), stdin);  //commandline을 받는다.
			new_argv[0] = strtok(_argv, " ");		//commandline에서 command를 파싱한다.

			//command line 에서 argument 부분을 파싱한다.
			for (i = 1; ; i++) {
				new_argv[i] = strtok(NULL, " ");
				if (!(new_argv[i]))		//파싱을 계속 하다가 끝까지가면 break
					break;
				new_argc++;
			}
			//\n 제거
			new_argv[new_argc - 1] = strtok(new_argv[new_argc - 1], "\n");
			//대신 NULL 입력
			new_argv[new_argc] = (char*)NULL;
			strcpy(command, new_argv[0]);    //command를 복사
			if (strcmp(command, "quit") == 0)   //만약 coommand가 quit명령어 이면 프로그램은 종료됨
				return 0;
			else if (strcmp(command, "cd") == 0) {
				chdir(new_argv[1]);
			}
		}
		//path를 파싱
		strcpy(copy_path, getenv("PATH"));
		modified_path = strtok(copy_path, ":");		//path는 ":"로 구분되어져있기 때문에 strtok를 이용한다.

		strcpy(real_path, modified_path);
		strcat(real_path, "/");
		strcat(real_path, command);//파싱한 path뒤에 command를 붙인다.
		strcat(real_path, "");

		//자식 프로세스 생성
		pid = fork();

		if (pid == -1) {
			printf("fork 실패 프로세스 \n");
			return -1;
		}
		//자식 프로세스
		if (pid == 0) {
			//path가 맞을 때 까지 무한 루프, 모든 path실패할 경우 탈출
			//char* envp[] = { "USER=user14", "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/jvm/java-11-openjdk-amd64/bin", (char*)0 };
			while (execv(real_path, new_argv) == -1) {		//execv(실행화일이 있는 곳까지의 전체경로 이름,
				//파싱										//		실행하고자 하는 프로그램의 인수들의 배열)
				
				modified_path = strtok(NULL, ":");
				if (!(modified_path))						//파싱 끝나면 break
					break;

				strcpy(real_path, modified_path);
				strcat(real_path, "/");
				strcat(real_path, command);

				strcat(real_path, "");

			}
			//자식프로세스가 명령을 수행하면 종료됨
			exit(0);
		}
		wait(NULL);

		//쉘로 동작하게하고,다시 COMMAND LINE을 받도록 다시 수정
		new_argc = 1;

	}
}
