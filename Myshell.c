#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void list(){
        printf("\n\n\nhostname : Show host's name\n"
                "list : Show exist command list\n"
                "ls : Show the file & dir in directory\n"
                "ps : Show the working process\n"
                "pwd : Show path\n"
                "repeat : fork more 5 times\n\n\n\n");
}

int main(int argc, char *argv[]){
        pid_t pid;
        int i;
        char str[255];
        printf("This program do fork 5 times\n");
        printf("'list' = show the command list\n");

        for(i = 0; i < 5; i++){
                pid = fork();
                if (pid == -1){
                        perror("fork error");
                        return 0;
                }
                else if (pid == 0) {
                        // child
                        printf("child process with pid %d (i: %d) \n", getpid(), i);
                        printf("Enter the command: ");
                        scanf("%s", str);
                        if (!strcmp(str, "list"))
                                list();
                        else if (!strcmp(str, "ls"))
                                execve("/bin/ls", argv, argv);
                        else if (!strcmp(str, "pwd"))
                                execve("/bin/pwd", argv, argv);
                        else if (!strcmp(str, "hostname"))
                                execve("/bin/hostname", argv, argv);
                        else if (!strcmp(str, "ps"))
                                execve("/bin/ps", argv, argv);
                        else if (!strcmp(str, "repeat"))
                                main(argc, argv);
                        else
                                printf("%s is not exist.\n\n", str);
                        exit (0);
                } else {
                        // parent
                wait(0);
                }
        }
        return 0;
}

