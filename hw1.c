#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(void)
{
        char *user;
        char *pwd;

        char input[255]; //입력
        char *output;//출력
        char buf[255];//입력값 넣기(임시저장)

        number = 0;
        tokens[number] = strok(input, "\n");

        while(1)
        {
                fgets(input, 255, stdin); //입력받음
                number = 0;
                tokens[number] = strtok(input," \n");

                input[strlen(input)-1] = '\0';//들어온 입력값 문자열 길이
                output = strtok(input, " "); //공백제거

                if(strcmp(output,"q")==0)//입력값이 q이면
                {
                        printf("프로그램종료\n");
                        break;
                }
                else if(strcmp(output,"ls")==0)//ls이면
                {
                        printf("ls 명령어 수행 \n");
                }
                else if(strcmp(output,"cd")==0)//cd이면
                {
                        printf("cd 명령어 수행 \n");
                }
                else
                {
                        printf("잘못된 명령어입니다. 다시입력해주세요.");
                }
        }

        pid = fork();
        if (pid==0){
                while(true){
                        if(

        user = getenv("USER");//user값 가져옴
        pwd = getenv("PWD");//PWD값 가져옴
        printf("user : %s\n",user);
        printf("pwd : %s\n",pwd);
        return 0;
}
