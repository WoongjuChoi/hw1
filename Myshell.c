#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h> // to use function strcmp()
#include <dirent.h>

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
        printf("\n\n\nlist : Show the function list\n"
                "cal : Execute calculator\n"
                "cat : Read & print file\n"
                "ls : Show the file in directory\n\n\n\n");
}

void file_list(){
        DIR *dir_info;
        struct dirent  *dir_entry;

        dir_info = opendir( ".");
        if(dir_info == NULL)
                printf("Cannot read dir.info.\n");
        if(dir_info != NULL){
                while(dir_entry = readdir(dir_info)) {
                        printf("%s\n", dir_entry->d_name);}}
        closedir(dir_info);
}

void cat(){

        char filename[256];
        char str[1024];
        FILE* asdf;
        printf("Enter the File name: ");
        scanf("%s", filename);
        asdf = fopen(filename, "r");
        if(!asdf){
                printf("Failed");
                exit(101);}
        while(!feof(asdf)){
            fgets(str, sizeof(str), asdf);
            printf("%s", str);
        }
}

int main(int argc, char *argv[])
{
        pid_t pid;
        int i;
        char str[255];
        printf("'list' = show list\n");
        for (i = 0; i < 5; i++) {
                pid = fork();
                if (pid == -1) {
                        perror("fork error");
                        return 0;
                }
                else if (pid == 0) {
                        // child
                        printf("Enter a String: ");
                        scanf("%s", str);
                        if (!strcmp(str, "cal"))
                                calculator();
                        else if (!strcmp(str, "list"))
                                list();
                        else if (!strcmp(str, "ls"))
                                file_list();
                        else if (!strcmp(str, "cat"))
                                cat();
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

