#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER 100

int main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	char file_name[BUFFER];
	char *fArr[20] = {NULL, };
	char path[BUFFER];
	

	printf("********************hw1*******************\n");

	while(1){
		getcwd(path, BUFFER);
		if(path ==  NULL){
			perror("current working directory get error");
			return 0;
		}

		printf("SiSH..%s$", path);
		fgets(file_name, BUFFER, stdin);
		if ((strcmp(file_name, "\n")==0))
			continue;

		int i = 0;
		char *ptr = strtok(file_name," ");
		
		while(ptr != NULL){
			fArr[i] = ptr;
			i++;

			ptr = strtok(NULL, " ");
		}

		pid = fork();
		if (pid == -1){
			perror("fork error");
			return 0;
		}
		else if(pid == 0){
			if (strcmp(fArr[0], "quit")==0){
				exit(0);
			}
			else if(strcmp(file_name, "ls\n")==0){
				execlp("/bin/ls","ls",NULL);
				exit(0);
			}
			//else if(strcmp(fArr[0], "cd")==0){
			//	int cDir = chdir(fArr[1]);

			//	if(cDir == -1)
			//		perror("directory change failed\n");
			//	exit(0);
			//}
			else
				exit(0);
			
		}
		else{
			wait(0);;
		}
		
		if(strcmp(file_name, "quit\n")==0)
			break;
	}
	printf("\nhw1.c end\n");
	return 0;
}
