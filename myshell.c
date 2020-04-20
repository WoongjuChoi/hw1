#include <stdio.h> // printf()
#include <stdlib.h> // exit()
#include <string.h> // perror(), strlen()
#include <unistd.h> // fork()
#include <sys/wait.h> // waitpid()
#include <sys/types.h>
#include <time.h>

#define MAX 255


void *prompt(char cmd[]){ // print prompt and get command from user
	char hName[MAX], uName[MAX], dName[MAX];
	void *ret; // variable to save return value

	gethostname(hName, MAX); // save host name
	getlogin_r(uName, MAX); // save user name
	getcwd(dName, MAX); // save directory name

	printf("SISH %s@%s:%s$ ", uName, hName, dName); // print current path

	ret = fgets(cmd, MAX, stdin);
	
	if(cmd[strlen(cmd)-1] == '\n') // convert '\n' to NULL
		cmd[strlen(cmd)-1] = 0; // can be recognized as string
	
	return ret;
}

void cmd_pwd(char cmd[]){
	char arg[MAX];
	printf("%s\n", getcwd(arg, MAX));
	return;
}

void cmd_user(char cmd[]){
	char arg[MAX];
	printf("%s\n", getenv("USER"));
	return;
}

void cmd_date(void){
	time_t now;
	time(&now);
	printf("%s", asctime(localtime(&now)));
	return;
}

void cmd_time(void){
	clock_t start, end;
	long i = 0;
	double result;
	start = clock();
	while(i < 3000000){
		i++;
	}
	end = clock();
	result = (double)(end-start);
	printf("%f\n", result);
	return;	
}

void cmd_ls(char cmd[]){
	return;
}

void cmd_cd(char cmd[]){
	char *arg;
		
	strtok(cmd, " ");
	arg = strtok(NULL, " ");

	if(arg == NULL){
		chdir(getenv("HOME"));
	}	
	else{
		chdir(getcwd(arg, MAX));
	}
	return;
}

void cmd_ls(char cmd[]){
	char path[MAX] = "/bin/";
	strcat(path, cmd);
	execve(path, cmd);
}

void cmd_fork(char cmd[]){
	pid_t pid;
	int status;
	char *arg;
	
	pid = fork();
	if(pid < 0){
		perror("fork error\n");
		return;
	}
	else if(pid == 0){ // child process
		printf("child process with pid %d\n", getpid());
		strtok(cmd, " "); //seperate string with blank
		arg = strtok(NULL, " "); // return NULL

		
		if(strcmp(cmd, "cd") == 0){
			cmd_cd(cmd);
				exit(0);
			}
			else if(strcmp(cmd, "ls\n") == 0){
				cmd_ls(cmd);
				exit(0);
			}
			else{
				execlp(cmd, cmd, arg, (char*) 0);
			}
		}
		perror("couldn't execute");
	}
	else{ // parent process
		printf("parent process with pid %d\n", getpid());
		wait(0);
	}
	return;
}

void cmd_help(char cmd[]){
	printf("\n--------------command list-----------------\n");
	printf("help\ncd\nuser\ndate\ntime\npwd\nexit\nquit\n");
	printf("--------------------------------------------\n\n");
}

int main(void){
	char cmd[MAX];
	char *dir;
	
	dir = getcwd(NULL, MAX);
	printf("\n==============program started==============\n");
	while(prompt(cmd)){

		if(strcmp(cmd, "") == 0){
			continue;
		}
		else if(strcmp(cmd, "exit") == 0){
			printf("==============program finished===========\n\n");
			exit(0);
		}
		else if(strcmp(cmd, "quit") == 0){
			printf("=========r====program finished===========\n\n");
			exit(0);
		}
		else if(strcmp(cmd, "ls") == 0){
			printf("cmd ls\n");
			cmd_fork(cmd);
		}
		else if(strcmp(cmd, "cd") == 0){
			printf("cmd cd\n");
			cmd_cd(cmd);
		}
		else if(strcmp(cmd, "pwd") == 0){
			cmd_pwd(cmd);
		}
		else if(strcmp(cmd, "user") == 0){
			cmd_user(cmd);
		}
		else if(strcmp(cmd, "date") == 0){
			cmd_date();
		}
		else if(strcmp(cmd, "time") == 0){
			cmd_time();
		}
		else if(strcmp(cmd, "help") == 0){
			cmd_help(cmd);
		}
		else{
			printf("잘못된 명령어\n");
		}
	}	
	//printf("===============program finished==============\n\n");
	return 0;
}

