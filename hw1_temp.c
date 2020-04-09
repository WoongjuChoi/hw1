#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int cd(char *path) {
	return chdir(path);
}

char **get_input(char *input) {
	char **command = malloc(8*sizeof(char *));
	if(command == NULL) {
		perror("malloc failed");
		exit(1);
	}
	char *separator = " ";
	char *parsed;
	int index = 0;

	parsed = strtok(input, separator);
	while(parsed != NULL) {
		command[index] = parsed;
		index++;

		parsed = strtok(NULL, separator);
	}

	command[index]= NULL;
	return command;
}

int main(void) {
	char **command;
	char *input = malloc(sizeof(char)*1024);
	pid_t child_pid;
	int stat_loc;

	while(1) {
		memset(input, 0x00, 1024); 
		printf("my_shell> ");
		fgets(input,strlen(input)-1,stdin);
		command = get_input(input);
		if(feof(stdin)) {
			printf("Ctrl+D exit \n");
			exit(0);
		}
		input[strlen(input)-1] = '\0';
		fflush(stdin);

		if(strcmp(command[0], "cd") == 0) {
			if(cd(command[1]) < 0) {
				perror(command[1]); 
			}
			continue;
		}
		
		if(execvp(command[0], command) < 0) {
			perror(command[0]);
			exit(1);
		}

		child_pid = fork();
		if(child_pid < 0) {
			perror("Fork Failed");
			exit(1);
		}else if(child_pid == 0) {
			execvp(command[0], command);
			printf("This won't be printed if execvp is successful\n");
		}else {
			wait(&stat_loc);
		}
		free(command);
		free(input);	
	}

	return 0;
}

	
