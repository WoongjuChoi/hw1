#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

void procLs(char* output)//Ls 로직 수행메소드
{
        //자신의 경로에 있는 모든 파일 탐색
        ////객체를 가져와서 ls뒤에 파싱한 값을 가지고 구현.
        printf("Ls로직구현");
}

void procCd(char* output)//Cd 로직 수행 메소드
{
        //해당 경로로 이동
        //객체를 가져와서 cd 뒤에 파싱한 값을 가지고 구현.
        printf("Cd로직 구현 ");
}

int main(void)
{
        char *user;
        char *pwd;

        char input[255]; //입력
        char *output;//출력
        char buf[255];//입력값 넣기(임시저장)

        //number = 0;
        //tokens[number] = strok(input, "\n");

        while(1)
        {
                fgets(input, 255, stdin); //입력받음
                //number = 0;
                //tokens[number] = strtok(input," \n");
                int length = strlen(input-1);
                input[strlen(input)-1] = '\0';//들어온 입력값 문자열 길이
                output[length] = strtok(input, " "); //공백제거

                if(strcmp(output[0],"q")==0)//입력값이 q이면
                {
                        printf("프로그램종료\n");
                        break;
                }
                else if(strcmp(output[0],"ls")==0)//ls이면
                {
                        printf("ls 메소드 호출 \n");
                        procLs(output);
                }
                else if(strcmp(output[0],"cd")==0)//cd이면
                {
                        printf("cd 메소드 호출 \n");
                        procCd(output);
                }
