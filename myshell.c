#include <stdio.h> // printf(), fgets(), perror(), ...
#include <stdlib.h> // exit(), getenv(), NULL, ...
#include <string.h> // strlen(), strcmp(), strtok(), ...
#include <unistd.h> // fork(), chdir(), getcwd(), ...
#include <time.h> // clock(), time(), ...
#include <sys/wait.h> // wait(), ...
#include <sys/types.h> // clock_t, time_t, ...

#define MAX 255 // max length

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

void cmd_pwd(char cmd[]){ // command 'pwd' - print current directory
	char arg[MAX];
	printf("%s\n", getcwd(arg, MAX));
	printf("*****\n\n");
	return;
}

void cmd_user(char cmd[]){ // command 'user' - print current user
	char arg[MAX];
	printf("%s\n", getenv("USER"));
	printf("*****\n\n");
	return;
}

void cmd_date(char cmd[]){ // command 'date' - print current date
	time_t now;
	time(&now);
	printf("%s\n", asctime(localtime(&now)));
	printf("*****\n\n");
	return;
}

void cmd_time(char cmd[]){ // command 'time' - print execution time
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
	printf("*****\n\n");
	return;	
}

void cmd_cd(char cmd[]){ // command 'cd' - change directory
	char *arg;
		
	strtok(cmd, " ");
	arg = strtok(NULL, " ");

	if(arg == NULL){
		chdir(getenv("HOME"));
	}	
	else{
		chdir(getcwd(arg, MAX));
	}
	printf("*****\n\n");
	return;
}

void cmd_ls(char cmd[]){ // command 'ls' - show list
	char path[MAX] = "/bin/";
	strcat(path, cmd);
	//execve(path, cmd);
}

void cmd_clear(char cmd[]){ // command 'clear' - clear everything
	system("clear");
}

void cmd_help(char cmd[]){ // command 'help' - show function
	printf("-----------------command list-------------------\n");
	printf("\t\t\tclear\n\t\t\tcd\n\t\t\tdate\n\t\t\texit\n\t\t\thelp\n\t\t\tls\n\t\t\tpwd\n\t\t\tquit\n\t\t\tuser\n\t\t\ttime\n");
	printf("--------------------------------------------------\n\n");
	return;
}

void cmd_fork(char cmd[]){ // command 'fork' - execute process
	pid_t pid;
	int status;
	char *arg;
	
	pid = fork();
	if(pid < 0){ // error
		perror("fork error\n");
		return;
	}
	else if(pid == 0){ // child process
		printf("child process with pid %d\n", getpid());
		printf("*****\n");
		strtok(cmd, " "); //seperate string with blank
		arg = strtok(NULL, " "); // return NULL
		
		if(strcmp(cmd, "ls\n") == 0){ // input: ls
			cmd_ls(cmd); // UDF - cmd_ls
			printf("*****\n\n");
			exit(0);
		}
		/*
		else if(strcmp(cmd, "cd") == 0){ // input: cd
			cmd_cd(cmd);
			exit(0);
		}
		*/
		else if(strcmp(cmd, "clear") == 0){ // input: clear
			cmd_clear(cmd);
			exit(0);
		}
		else if(strcmp(cmd, "pwd") == 0){ // input: pwd
			cmd_pwd(cmd); // UDF - cmd_pwd
			exit(0);
		}
		else if(strcmp(cmd, "user") == 0){ // input: user
			cmd_user(cmd); // UDF - cmd_user
			exit(0);
		}
		else if(strcmp(cmd, "date") == 0){ // input: date
			cmd_date(cmd); // UDF - cmd_date
			exit(0);
		}
		else if(strcmp(cmd, "time") == 0){ // input: time
			cmd_time(cmd); // UDF - cmd_time
			exit(0);
		}
		else if(strcmp(cmd, "help") == 0){ // input: help
			cmd_help(cmd); // UDF - cmd_help
			exit(0);
		}	
		else{
			execlp(cmd, cmd, arg, (char*) 0);
		}
		perror("couldn't execute");
	}
	else{ // parent process
		printf("\n*****\n");
		printf("parent process with pid %d\n", getpid());
		wait(0);
	}
	return;
}

int main(void){ // main
	char cmd[MAX];
	char *dir;
	dir = getcwd(NULL, MAX); // save current directory

	printf("\n==============program started==============\n");
	while(prompt(cmd)){ // prompt input exists

		if(strcmp(cmd, "") == 0){ // input: \n
			continue;
		}
		else if(strcmp(cmd, "exit") == 0){ // input: exit
			printf("==============exit program===========\n\n");
			exit(0);
		}
		else if(strcmp(cmd, "quit") == 0){ // input: quit
			printf("==============quit program===========\n\n");
			exit(0);
		}
		// input: clear, ls, pwd, user, date, time, help
		else if(!(strcmp(cmd, "clear")) | !(strcmp(cmd, "ls")) | !(strcmp(cmd, "pwd")) | !(strcmp(cmd, "user")) | !(strcmp(cmd, "date")) | !(strcmp(cmd, "time")) | !(strcmp(cmd, "help"))){
			cmd_fork(cmd);
		}
		else if(strcmp(cmd, "cd") == 0){ // input: cd
			cmd_cd(cmd);
		}
		else{ // command out of list
			printf("wrong command\n\n");
		}
	}	
	return 0;
}

