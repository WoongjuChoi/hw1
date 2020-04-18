#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAX_PATH 100
#define LF 10
int print_prompt(){
	char *buffer =(char *)malloc(MAX_PATH);
	char *value=(char*)getcwd(buffer,MAX_PATH);
       	if(value !=0)	fprintf(stdout,"shell:%s>",buffer);
	free(buffer);
        return 0;
}
int main(int argc,char *argv[],char *envp[]){
       char c;
       char cmd[80];
       char *vecl[10];
       setbuf(stdout,NULL);
       print_prompt();
       while(fgets(cmd,80,stdin)!=NULL){
	       int i=0;
	       cmd[strlen(cmd)-1]='\0';
	       memset(vecl,0x00,sizeof(vecl));
	       char *token;
	       token=strtok(cmd,"");
	       while(token){
		    vecl[i]=token;
		    token=strtok(NULL,"");
		    i++;
		   }
             if(fork()==0){
		     char path[100]="/bin/";
		     strcat(path,vecl[0]);
		     execve(path,vecl,envp);
		     exit(0);
	     }
	     else{
		     wait(0);
		     print_prompt();
		 }
       }
       return 0;
}

