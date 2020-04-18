//
//  main.c
//  ItsMyShell
//
//  Created by 형주 on 2020/04/16.
//  Copyright © 2020 형주. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif
void hy_cd(int ac, char *av){
    char *path;
    if(ac > 1) path = av;
    else if ((path = (char*)getenv("HOME")) == NULL) path = ".";
    if (chdir(path) < 0 ) {
        printf("error");
    }
}

int main() {
    printf("\n*****If you want to end this shell plz enter --quit-- ******\n");
    while(1)
    {

        char *tokens[1024];
        int token_count;
        char line[1024];
        char real_path[1024];
        char copy_path[1024];
        char* modified_path;
        char *username = NULL;
        char strBuffer[_MAX_PATH] = { 0, };
        char *pstrBuffer = NULL;
        time_t ct;
        struct tm tm;
        
        //프롬포트 설정
        pstrBuffer = getcwd( strBuffer, _MAX_PATH ); //현재디렉토리
        username = getenv("USER"); // user이름
        ct = time(NULL);
        tm = *localtime(&ct);//시간 받아오기
        printf("[%s]: %d:%d:%d %s ~ $ ",username, tm.tm_hour, tm.tm_min, tm.tm_sec, pstrBuffer);
        //프롬포트 [이름]: 시간 현재dir
       
        
        //입력 받기
        fgets(line,sizeof(line),stdin);
        pid_t child;
        
        token_count=0;
        tokens[token_count] = strtok(line,"    \n");
        
        while(tokens[token_count] != NULL && token_count < 1024)
        {
           tokens[++token_count] = strtok(NULL,"    \n");
        }
    
        
        //quit 구현
        if (strcmp(tokens[0], "quit") == 0) {
         printf("                *****  Shell ended  *****\n");
            exit(1); // 종료
        
        }
        //cd 구현
        if(strcmp(tokens[0],"cd") == 0){
            if(tokens[1] == NULL){
                printf("please enter the dir\n");
            }else{
                hy_cd(2, tokens[1]);
            }
            continue;
        }
       
       //PATH 받아 파싱
        strcpy(copy_path, getenv("PATH"));
        modified_path = strtok(copy_path, ":");
        strcpy(real_path, modified_path);
        strcat(real_path, "/");
        strcat(real_path, tokens[0]);
        strcat(real_path, "");
        
      //fork하고 pid에 따라 실행
        child = fork();
        if ( child == 0)
        {
        
                while(execve(real_path,tokens,NULL) == -1){
                    if(!(modified_path = strtok(NULL, ":")))
                        break;
               
                    strcpy(real_path, modified_path);
                    strcat(real_path, "/");
                    strcat(real_path, tokens[0]);
                    strcat(real_path, "");
                }
            exit(1);
        }
        else if ( child == -1)
        {
            printf("error");
            exit(1);
        }
        else if (child != 0)
        {
            wait(&child);
        }
        
    }
    return 0;
}

