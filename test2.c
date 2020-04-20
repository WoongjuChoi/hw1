#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_B 1024

void PATH_DES(char real_path[MAX_B], char* modified_path, char cmd[MAX_B]) {
	strcpy(real_path, modified_path);
	strcat(real_path, "/");
	strcat(real_path, cmd);
	strcat(real_path, "");
}
bool FK(char* FKRUN) {
	
	int argc;
	char** argv;
	char cmd[254];
	char* get_order[MAX_B]; //수정한 argument vector를 저장하기위한 배열
	char order[MAX_B]; //수정한 argument vector를 저장하기위한 변수
	char* modified_path;

	char copy_path[MAX_B];
	char real_path[MAX_B];
	int new_argc;
	int cmd_argu;
	new_argc = argc;

	pid_t child_pcs;

	if (new_argc == 1) {
		fgets(order, sizeof(order), stdin);
		get_order[0] = strtok(order, "\t\n");
	}
	for (cmd_argu = 1; ; cmd_argu++) {
		if (!(get_order[cmd_argu] = strtok(NULL, " ")))
			break;
		new_argc++;
	}

	get_order[new_argc - 1] = strtok(get_order[new_argc - 1], "\n");
	get_order[new_argc] = (char*)NULL;
	strcpy(cmd, get_order[0]);

	if (strcmp(cmd, "quit") == 0) {
		printf("quit!!");
		return 0;
	}
	else if (strcmp(cmd, "cd") == 0) {
		chdir(get_order[1]);
	}


	strcpy(copy_path, getenv("PATH"));
	modified_path = strtok(copy_path, ":");
	PATH_DES(real_path, modified_path, cmd);

	child_pcs = fork();
	if (child_pcs == -1)
	{
		perror("fork error\n");
		return -1;
	}
	else if (child_pcs == 0)
	{
		while (execv(real_path, get_order) == -1) { 
			if (!(modified_path = strtok(NULL, ":")))
				break;
			PATH_DES(real_path, modified_path, cmd);
		}
		exit(0); // child process를 종료
	}
	else{
	wait(NULL);}
	new_argc = 1;
}

int main()
{
	
	printf("Own shell (if you want to exit your shell, enter -quitkey-i\n");
	char FKRUN[MAX_B];
		while (1) {
			fgets(FKRUN, sizeof(FKRUN), stdin);
			if (FK(FKRUN) == 0) break;

		}
		return 0;
	} 
