#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>

#define COMMAND_SIZE 1000
#define MAX_ARGS 50
#define NAMES_SIZE 500

void prompt();
void read_cmd(char *[]);
void exec(char *[]);
void cd(char *[]);
void pwd(char *[]);

int main(int argc, char const *argv[])
{
	char *cmd_arg[MAX_ARGS];

	do {

		prompt();
		read_cmd(cmd_arg);
		exec(cmd_arg);

	} while (1);
}

void prompt()
{
	char *home_dir = getenv("HOME");
	char current_dir[NAMES_SIZE];
	getcwd(current_dir, NAMES_SIZE);

	if (strncmp(home_dir, current_dir, strlen(home_dir)) == 0) {
		strcpy(current_dir,current_dir + strlen(home_dir) - sizeof(char));
		current_dir[0] = '~';
	}

	char hostname[NAMES_SIZE];
	gethostname(hostname, NAMES_SIZE);
	printf("[32183520_shell] %s@%s:%s$ ",getenv("LOGNAME"), hostname, current_dir);
}

void read_cmd(char *cmd_arg[])
{
	char command[COMMAND_SIZE];
	fgets(command, COMMAND_SIZE, stdin); 

	int i = strlen(command) - 1;
	while (isspace(command[i]))
		command[i--] = '\0';

	cmd_arg[i = 0] = strtok(command, " ");
	while (cmd_arg[i] != NULL && i < MAX_ARGS)
		cmd_arg[++i] = strtok(NULL, " ");

}

void exec(char *cmd_arg[])
{
	if (strcmp(cmd_arg[0], "exit") == 0) {
		printf("32183520_shell program exit!\n");
		exit(0);
	}
	else if (strcmp(cmd_arg[0], "cd") == 0) {
		cd(cmd_arg);
	}
	else if (strcmp(cmd_arg[0], "pwd") == 0) {
		pwd(cmd_arg);
	}
	else {
		pid_t pid = fork();
		if (pid < 0) {
			printf("Error");
		}
		else if (pid > 0) { 
			int status;
			wait(&status); 
		}
		else {  //execunting child
			execvp(cmd_arg[0], cmd_arg);
			perror("error");
			abort();
		}
	}
}

void cd(char *cmd_arg[])
{
	if (cmd_arg[1] == NULL) {
		chdir(getenv("HOME"));
	}
	else if (chdir(cmd_arg[1]) < 0) {
			printf(" %s: no such directory\n", cmd_arg[1]);
	}
}

void pwd(char *cmd_arg[])
{
	char *home_dir = getenv("HOME");
	char current_dir[NAMES_SIZE];
	getcwd(current_dir, NAMES_SIZE);

	if (strncmp(home_dir, current_dir, strlen(home_dir)) == 0) {
		strcpy(current_dir, current_dir + strlen(home_dir) - sizeof(char));
		current_dir[0]=' ';
	
	}

	char hostname[NAMES_SIZE];
	gethostname(hostname, NAMES_SIZE);
	printf("[print working directory] home%s \n", current_dir);
}
