#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
#define BUF_NUM 1024

/*char* str_num(char *str1)
{
        char* str2;
        char* str3;
        int i=0;

        str2=strtok(str1, " ");

        while(str2!=NULL)
        {
                i++;
                strcpy(str3, str2);
                str2=strtok(NULL, " ");
        }
        return str3;

}*/

int main(int argc, char *argv[])
{
        pid_t pid;

        char filename[SIZE];
        char* file_f;
        char cwd[BUF_NUM];
        char buf[SIZE];

        printf("----------------------------------\n");

        while(1){
                printf("user09@os-lecture—-1:~$ ");
                fgets(filename,SIZE, stdin);
                filename[strlen(filename)-1]='\0';

                if(strcmp(filename,"quit")==0){
                    printf("--------------quit--------------\n");
                    break;
                }
                /*if(str_num(filename)!=NULL)
                        {
                                printf("%s\n",str_num(filename));
                }*/
            pid=fork();

            if(pid<0){
                fprintf(stderr, "fork failed");
                exit(1);
            }
            else if(pid ==0){
                if(strcmp(filename,"ls")==0){
                    execlp("/bin/ls","ls",NULL);
                    exit(0);
                }
                if(strcmp(filename,"\n")==0){
                    continue;
                }
                if(strcmp(filename,"pwd")==0){
                    system("pwd");
                    exit(0);
                }
                /* if(str_num(filename)!=NULL){
                        if(chdir(str_num(filename))!=0){
                            perror("failed");
                        }else{
                            getcwd(cwd, sizeof(cwd));
                            printf("%s\n",cwd);
                            exit(0);
                        }
                 }*/
                if(strcmp(filename, "ls -b")==0){
                         system("ls -b");
                         exit(0);
                }
                if(strcmp(filename, "ls -a")==0){
                         system("ls -a");
                         exit(0);
                }
                if(strcmp(filename, "ls -l")==0){
                         system("ls -l");
                         exit(0);
                }
                exit(0);
            }
            else{
                wait(NULL);
            }
        }
        return 0;
}

