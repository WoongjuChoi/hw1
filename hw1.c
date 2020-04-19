#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//프롬프트 함수
void type_prompt()
{ 
    static int first_time = 0;
    if(first_time == 0){
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);
	printf(" user name : %s user path : %s  present time : %d-%d-%d %d:%d:%d\n", getenv("USER"),getenv("PWD"),tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("#");
	}
	else {
		printf("#");
	}
}
//사용자 명령 읽기
void read_command(char cmd[], char* par[])
{
	char line[1024];
	int count = 0, i = 0, j = 0;
	char * array[100], * pch;

	//read line
	for (;;) {
		int c = fgetc(stdin); 
		line[count++] = (char)c;
		if (c == '\n')break;
	}
	if (count == 1)return;
	pch = strtok(line, "\n");

	while (pch != NULL) {
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}
	strcpy(cmd, array[0]);
	for (int j = 0; j < i; j++)
		par[j] = array[j];
	par[i] = NULL;
}


int main(void)
{
	char cmd[1000], command[100], * parameters[20]; //cmd, command는 명령어들을 저장하는 변수이다 .
	char* envp[] = { (char*)"PATH=/bin",0 };  
    pid_t pid;
    int i =0;  //프로세스 제어용 변수
	type_prompt();
	pid = fork();
    //무한루프 시작         
	while (1) {
		if (pid == -1) {
			perror("fork error");
			return 0;
		}
		if (pid == 0) {
			type_prompt();
		    read_command(command, parameters);
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp);
			if (strcmp(command, "exit") == 0)
				exit(0);
		}
		else {
			wait(0);
			return 0;
		}
	}
	return 0;
}
