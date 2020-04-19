#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include<string.h>

void type_prompt()
{
	pritf("#");
}

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
	char cmd[1000], command[100], * parameters[20];
	char* envp[] = { (char*)"PATH=/BIN",0 }; 
	while (1) {
		type_prompt();
		read_command(command, parameters);
		if (fork() != 0)
			wait(NULL);
		else {
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp);
		}
		if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}