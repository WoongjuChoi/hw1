#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void read_command (char cmd[], char *par[] ){
	char line[1024];
	int count =0, i=0, j=0;
	char *array[100], *pch;

	//Read one line
	for( ;;){
		int c= fgetc (stdin);
		line[count++] =(char) c;
		if (c=='\n') break;
	}
	if (count ==1) return;
	pch = strtok (line, " \n");

	//parse the line into words
	while( pch !=NULL){
		array[i++] = strdup (pch);
		pch= strtok(NULL, "\n");
	}
	//first word is command
	strcpy(cmd, array[0]);

	//others are parameters
	for(int j=0; j<i;j++)
		par[j]=array[j];
	par[i]=NULL;
}

void type_prompt(){
	static int first_time =1;
	if (first_time ){//처음화면이면
		const char * CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J"; //e는 escape
		write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
		first_time=0;
	}
	printf("32153306#"); //display prompt
}

int main()
{
	char cmd[100], command[100], *parameters[20];
	char *envp[] ={ (char *) "PATH=/bin", 0}; //environment variable
	while(1) {	//repeat 
		type_prompt(); //display prompt
		read_command ( command, parameters); //terminal에서 input받음
		if(fork()!=0) //parent process
			wait(NULL);
		else {
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp); //command 수행
		}
		if (strcmp (command, "quit" ) ==0)
			break;
	}
	return 0;
}

