#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void help()
{
	printf("* * * * * * * * * * * HELP* * * * * * * * * * * \n");
	printf("quit : 프로그램 종료 \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * \n");

}

int main()
{

	char line[100];
	char *ptr;


	while (1)
	{
		printf("[hayeon]:~$ ");

		fgets(line, sizeof(line), stdin); //명령어 입력받기

		if (line[0] == '\n') //엔터 입력시 아무 출력 없음
			continue;

		line[strlen(line) - 1] = '\0';
		ptr = line;


		if (strcmp(ptr, "quit") == 0) { //quit입력시 프로그램 종료
			return 0;
		}

		if (strcmp(ptr, "help") == 0) { //help입력시 도움말
			help();
		}

	}
	return 0;

}
