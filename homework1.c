#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


//프롬프트 함수
void type_prompt()
{ 
	static int firsttime = 1;
	if(firsttime) {
		printf("first time USER : %s PATH : %s \n ",getenv("USER"), getenv("PATH"));
		firsttime =0;     
	}          
	printf("$");
}
//사용자 명령 읽기
void read_command(char cmd[], char* par[])
{
             //입력 후 명령어 읽음
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;
	for (;;)
	{
		int c = fgetc(stdin);
		line[count++] = (char)c;
		if (c == '\n')break;

	}
	if (count == 1)return;
	pch = strtok(line, "\n");
             //엔터 키(개행문자)를 가져온 단어에서 제거
	while (pch !=NULL)
	{
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}
	strcpy(cmd,array[0]);
	for (int j = 0; j < i; j++)
		par[j] = array[j];
	par[i] = NULL; //후에 exe를 위해 parameter list에 null을 넣음
}


int main(void)
{
	char cmd[1000], command[100], * parameters[20]; //명령어을 저장하는 배열과 parameter를 저장할 포인터
	char* envp[] = { (char*)"PATH=/bin",0 }; //  환경변수, 명령은 bin에 있기 때문에 PATH=/bin 
	while (1) {
		type_prompt(); //프롬프트 시작
		read_command(command, parameters); // 명령을 읽게하는 함수
		if (fork() != 0) //자식 프로세스 생성
			wait(NULL); // 부모 프로세스는 대기
		else
		{
			strcpy(cmd, "/bin/"); //bin 디렉토리를 복사함
			strcat(cmd, command); //사용자 명령 합쳐줌
			execve(cmd, parameters, envp); // 명령을 실행
		}
		if (strcmp(command, "exit") == 0)  //빠져나기 위한 exit
			break;
	}
	return 0;
}
