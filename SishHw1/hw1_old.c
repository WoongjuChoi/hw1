#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char arr[50];
	pid_t pid;

	while(1)
	{
		pid = fork();

		if(pid < 0) // fail
		{
			perror("fork error");
			return 0;
		}

		else if(pid == 0) // Child
		{
			char **ptr = NULL;  //이중포인터로 문자열넣을 메모리생성
			ptr = (char**)malloc(sizeof(char*)*10);
			for(int i = 0; i < 10; i++)
				ptr[i] = (char*)malloc(sizeof(char)*10);
			
		
			char command[50]; char option[50];
			printf("Command Input: ");
			scanf("%[^\n]", arr); // input
			
			// exit : 종료
			char s[10] = "exit";
			int ret = strcmp(s, arr);
			if(ret == 0)
			{
				int val = 9;
				exit(val);
			}
			
			

			char *tok = strtok(arr, " ");
			int cnt = 0;
			while(tok != NULL)
			{
				if(cnt == 0)
					strcpy(command, tok);

				else if(cnt == 1)
					strcpy(option, tok);
			
				tok = strtok(NULL, " ");
				cnt++;
			}

			char arr2[50] = "./";
			strcat(arr2, command); // 붙임
			strcpy(ptr[1], option);
			strcpy(ptr[0], arr2); // ptr[0]: ./명령어
			ptr[2] = NULL; // ptr의 마지막에 null값 삽입

			execv(ptr[0], ptr+1); // 프로그램 실행

			for(int i = 0; i < 10; i++) // 메모리 free
				free(ptr[i]);
			free(ptr);

			exit(0);	
		}

		else // parent
		{
			int childval = -1;
			wait(&childval);
			childval /= 255; // 255로 나눠줘야함
			if(childval == 9) return 0;

		}

	}

	return 0;
}
