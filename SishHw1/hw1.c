#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int start(char* arr)
{
        char* tk[1000]; // 명령어 저장

        ////////////// 문자열 나누기
        tk[0] = strtok(arr, "  \n "); // tk[0]에 첫 명령어

        int i = 0; //tk[1]부터 저장
        while(tk[i] != NULL && i < 1000) // 명령어 나눠서 배열 tk[]에 저장
        {
                i++;
                tk[i] = strtok(NULL, "  \n");
        }

         /////// new_path 만들기
        char new_path[200];
        char temp[200];
        char* temp_path; // path 임시 저장

        strcpy(temp, getenv("PATH")); // PATH 환경변수 temp에 저장
        temp_path = strtok(temp, ":"); // 환경변수는 : 로 구분되있음
        strcpy(new_path, temp_path);
        strcat(new_path, "/");
        strcat(new_path, tk[0]); // 경로 뒤에 명령어 붙임
        strcat(new_path, ""); // 맨뒤 null 필요


        ///////// Change Directory
        if(strcmp(tk[0], "cd") == 0)
        {
                if(!tk[1]) // tk[1]에 아무값이 없다면 home 디렉토리로
                        chdir("/home/user37");
                else if(tk[1]) // tk[1] 이름 디렉토리로 이동
                        chdir(tk[1]);

                return 0;
        }

        ////// quit 명령
        if(strcmp(tk[0], "quit") == 0) // tk[0]이 quit이면Shell 종료
        {
                printf("Shell Ends\n");
                return 1;
        }


        pid_t pid = fork(); // fork

        /////////// 프로세스 분리
        if(pid < 0) // fail
        {
                perror("fork error\n");
                return 0;
        }

        else if(pid == 0) // child process
        {
                while(execv(new_path, tk) == -1) // 실행이안됬다면
                { //환경변수 모두 찾아봤는데도 없으면? break
                        // 환경변수 자른 뒤부분을 temp_path에
                        if(!(temp_path = strtok(NULL, ":")))
                                break; // 끝에 도달


                        strcpy(new_path, temp_path);
                        strcat(new_path, "/");
                        strcat(new_path, tk[0]);
                        strcat(new_path, "");
                }
                perror("fork error\n");
                return 0;
        }

        else // parent process
        {
                wait(0); // child 끝날때까지 대기
        }

        return 0;


}

int main()
{
        char arr[1000];
        int condition = 0;


        while(1)
        {
                printf("Enter quit to end.\n");
                printf("Input Order: ");
                fgets(arr, sizeof(arr), stdin);
                // quit에 의해 false 반환되면 종료
                condition = start(arr);
                if(condition == 1)
                        break;
        }

        return 0;
}
                                                 
