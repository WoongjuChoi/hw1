#include <stdlib.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
		int i = 0;
		char *stop = "quit";
		bool Go, Shell_go = true;	//루프를 돌지 안돌지에 대한 불리안값.
		int state;
		char str[80];
		print("Shell 프로그램의 종료를 원할 시에, '종료'를 입력해주세요. \n");
		pid_t pid;

		while (Shell_go) {
				char FilenName[100];	//사용자 입력 파일 이름 저장 공간
				scanf("%s", FilenName);
				printf("Filie name : %s를 검색합니다", FilenName);

				char *Value;
				Value = getenv(FilenName[1]);

				if (Value != NULL)
				{
					printf("해당 파일 ( %s)을 찾았습니다.\n 해당 파일 환경변수 : %s", FilenName, Value);
				}


					//1. fork발신자의 사본 생성. (부모 fork 호출 - 자식 process ID 반환, 자식 fork 호출 - 0 반환

				pid = fork();//fork 생성

				if (pid < 0) {		//0보다 작을 경우 에러 (-1)
					printf("PID 오류 발생.\n");
					return -1;

				}
				else if (pid == 0) {			//자식 프로세스
					printf("child %d. id : %d\n", i, (long)getpid());
					exit(0);
				}
				else {				//부모 프로세스
					printf("parent  id : %d\n", (long)getpid());
					wait(0);
				}
			

	
				printf("종료를 원할 시에는, 'quit'문자열을 입력해주세요.\n");
				scanf("%s", str);

				if (strcmp(str, stop) == 0) {
					printf("프로그램을 종료합니다.\n");
					Shell_go = false;

				}
				else {
					print("계속해서 프로그램을 실행합니다.\n");
					i++;
				}

		}

	return 0;
}
