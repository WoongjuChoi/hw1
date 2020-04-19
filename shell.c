#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXARG 7

int main()
{
    char buf[256];
    char *arg[MAXARG];
    char *s;
    char *save;
    int argv;
    
    static const char delim[] = " \t\n";
    int  status;
    char pwd_buf[256];
    char command[100];

    char* cut_path;     
    char copy_path[500];
    char new_path[500]; 
   	
    pid_t child;
    
    printf("-----start shell-----\n");
    
    while(1) {
  

       getcwd(pwd_buf,256);
       printf("%s@ %s  ", getenv("USER"), pwd_buf);     
       
       fgets(buf,256,stdin);
       argv = 0;
       
       s = strtok_r(buf, delim, &save);
       while(s) {
          arg[argv++] = s;
          s = strtok_r(NULL, delim, &save);
       }
       
       arg[argv] = (char *)0;
       strcpy(command, arg[0]);  
 
       if(strcmp(command,"quit")==0) {
	  printf("-----exit shell-----\n");		
          return 0;
       }  
       
       else if(strcmp(command,"cd") == 0) {
	    if( argv == 1 )
                	chdir( getenv( "HOME" ) );
                else if( argv == 2 ){
         		if( chdir( arg[1] ) )
               		printf( "No directory\n" );
        }
             	else
         	        printf( "USAGE: cd [dir]\n" );
	
	 
        }

        strcpy(copy_path, getenv("PATH"));
        cut_path = strtok(copy_path, ":");
        strcpy(new_path, cut_path);
        strcat(new_path, "/");
        strcat(new_path, command);
        strcat(new_path, "");

        child = fork();

        if(child == -1){
            printf("fork 실패 \n");
            return -1;
        }

        if(child == 0) {
            while(execv(new_path,arg)== -1){
                if(!(cut_path = strtok(NULL, ":")))
                    break;
                strcpy(new_path, cut_path);
                strcat(new_path, "/");
                strcat(new_path, command);
                strcat(new_path, "");

            }
            exit(0);
        }
        wait(NULL);
	argv = 1;
    }
}

       

