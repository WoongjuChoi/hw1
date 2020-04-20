#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
	printf("exit = [q] \n");
        printf("--------------------------------------------\n");


                        char cmd[254];
                        char* get_order[1024]; //수정한 argument vector를 저장하기위한 배열
                        char order[1024]; //수정한 argument vector를 저장하기위한 변수
                        char* modified_path;

                        char copy_path[1024];
                        char real_path[1024];
                        int new_argc;
                        int cmd_argu;
                        new_argc = argc;

                        pid_t child_pcs;

                while(1){
                        if (new_argc == 1) {
                                fgets(order, sizeof(order), stdin);
                                get_order[0] = strtok(order, "\t\n");
                        }
                        for (cmd_argu = 1; ; cmd_argu++) {
                                if (!(get_order[cmd_argu] = strtok(NULL, " ")))
                                break;
                                new_argc++;
                        }

                        get_order[new_argc -1] = strtok(get_order[new_argc -1],"\n");
                        get_order[new_argc] = (char*)NULL;
                        strcpy(cmd, get_order[0]);

                        if (strcmp(cmd, "q") == 0) {
                                printf("exit");
                                break;
                        }
                        else if (strcmp(cmd, "cd") == 0) {
                                chdir(get_order[1]);
                        }


                        strcpy(copy_path, getenv("PATH"));
                        modified_path = strtok(copy_path, ":");
                        strcpy(real_path, modified_path);
                        strcat(real_path, "/");
                        strcat(real_path, cmd);
                        strcat(real_path, "");

                        child_pcs = fork();

                        if (child_pcs == 0) {
 			while (execv(real_path, get_order) == -1) {
                                        if (!(modified_path = strtok(NULL, ":")))
                                                break;
                                        strcpy(real_path, modified_path);
                                        strcat(real_path, "/");
                                        strcat(real_path, cmd);
                                        strcat(real_path, "");
                                        }
                                exit(0); //자식프로세스를 종료한다.
                                }
                        else if(child_pcs == -1){
                                printf("warning : error");
                                return -1;
                                }
                        else if(child_pcs != 0){
                                wait(NULL); //waiting child
                        }
                        //쉘로 다시 만들어주기 위해서는 다시 COMMAND LINE을 받도록 해야한
                        new_argc=1;

        }         
}  
