#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h> // to use function strcmp()

void calculator(){
        int input = 0, a = 0, b = 0;

        printf("Please enter two integer: ");
        scanf("%d %d", &a, &b);
        printf("What do you want?\n(1.add, 2.sub, 3.mul, 4.div)");
        scanf("%d", &input);
        switch(input){
                case 1: printf("%d + %d = %d\n\n", a, b, a+b); break;
                case 2: printf("%d - %d = %d\n\n", a, b, a-b); break;
                case 3: printf("%d * %d = %d\n\n", a, b, a*b); break;
                case 4: printf("%d / %d = %f\n\n", a, b, (float)a/(float)b); break;
                default : printf("Don't you want nothing?\n\n");
        }

}

void list(){
        printf("\n\n\nlist : show the function list\n"
                "cal : execute calculator\n\n\n\n");
}



int main(int argc, char *argv[])
{
        pid_t pid;
        int i;
        char str[255];
        printf("'list' = show list\n");
        while (i = 0; i < 5; i++) {
                pid = fork();
                if (pid == -1) {
                        perror("fork error");
                        return 0;
                }
                else if (pid == 0) {
                        // child
                        printf("Enter a String: ");
                        scanf("%s", str);
                        if (!strcmp(str, "cal")){
                                calculator();}
                        else if (!strcmp(str, "list")){
                                list();}
                        else {
                                printf("%s is not exist.\n\n", str);}
                        exit (0);
                } else {

                        // parent
                wait(0);
                }
        }
        return 0;
}
