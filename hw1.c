#include<stdio.h
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(void)
{
        char *user;
        char *pwd;

        char input[255]; //출력
        char *output;
        char buf[255];

        while(1)
        {
                fgets(input, 255, stdin);
                input[strlen(input)-1] = '\0';
                output = strtok(input, " ");

                if(strcmp(output,"q")==0)
                {
                        printf("프로그램종료\n");
                        break;
                }
                else if(strcmp(output,"ls")==0)
                {
                        printf("ls 명령어 수행 \n");
                }
                else if(strcmp(output,"cd")==0)
                {
                        printf("cd 명령어 수행 \n");
                }
                else
                {
                        printf("잘못된 명령어입니다. 다시입력해주세요.");
                }
        }

        user = getenv("USER");
        pwd = getenv("PWD");
        printf("user : %s\n",user);
        printf("pwd : %s\n",pwd);
        return 0;
}
