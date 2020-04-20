#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


void function(char *command, char **sArr)
{
    int j;
    char *str, *next_ptr;
    for (int i = 0; i < 100; i++)
    {
        sArr[i] = NULL;
    }

    for (j = 1, str = command;; str = NULL, j++)
    {
        sArr[j] = strtok_r(str," ,\t\n", &next_ptr);
        if (sArr[j] == NULL || strcmp(sArr[j],"\n")==0)
            break;
    }
    // for (int i = 0; i < 10; i++)
    // {
    //     if (sArr[i] != NULL)
    //         printf("%s\n", sArr[i]);
    // }
    return;
}


int main(int argc, char *argv[])
{
	puts("myshell powered by DOSIMPACT");

	pid_t pid;
	int i;
	char userInput[100];
	//----------------------------------------------
	char* saveptr,str;
    char *sArr[100] = {
        NULL,
    };
	int iCounter = 0;
	
	while(1){
		printf("myshell:user:pwd#");
		fgets(userInput,100,stdin);
		
		if(strcmp(userInput,"quit\n")==0){
			puts("MY SHELL EXIT");
			break;
		}
		//printf("your inputs :  %s",userInput);
		function(userInput, sArr);
		sArr[0] = argv[0];
			
		pid = fork();
		if(pid == -1){
			perror("ERROR: fork fail");
		}
		else if(pid == 0){
			// printf("childProcess... %s\n",userInput);
			execv("./child",sArr);
			exit(0);
		}else{
			wait(0);
		}
		
	}

	return 0;
}




//TODO LIST

//1. 사용자의 입력을 받아서 단순히 출력해주는 프로그램 ✅

//2. 자식 프로세스한테 fork 해서 단순히 출력해주기. ✅

//2. 자식 프로세스에서, exec사용해, 단순이 인자값 출력하는 프로그램 ✅

//3. getenv key 입력이 올바르면, value출력해 주기