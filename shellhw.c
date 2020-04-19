#include<stdio.h>  
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/stat.h>
#define MAX_PATH 100
#define LF 10
#define TRUE 1
#define FALSE 0
#define ERROR (-1)
int print_prompt(){
	char *buffer =(char *)malloc(MAX_PATH);
	char *value=(char*)getcwd(buffer,MAX_PATH);
       	if(value !=0){
		fprintf(stdout,"shell:%s>",buffer);
	}
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
             if(!strcmp(vecl[0],"quit")){
		     exit(1);
		    }

             if(fork()==0){
	         if((!strcmp(vecl[0],"ls"))|(!strcmp(vecl[0],"cat"))|(!strcmp(vecl[0],"pwd"))){
		     char path[100]="/bin/";
		     strcat(path,vecl[0]);
		     execve(path,vecl,envp);
		  }
		 if(!strcmp(vecl[0],"cd")){
	             char *wrd;
		     char *context;
		     const char *delim="cd ";
		     wrd=strtok_r(vecl[0],delim,&context);
		     char *n_path;
		     char *cdbuffer=(char *)malloc(MAX_PATH);
		 
		     if(wrd==NULL){
			     chdir(getenv("HOME"));
			     n_path=(char *)getcwd(cdbuffer,MAX_PATH);
			     fprintf(stdout,"dir:%s\n",cdbuffer);
		      }
		      else{
			      chdir(getenv(wrd));
			      n_path=(char *)getcwd(cdbuffer,MAX_PATH);
		              fprintf(stdout,"ndir:%s\n",cdbuffer);
			  }
			free(cdbuffer);   
		   }
		     exit(0);
	     }
	     else{
		     wait(0);
		     print_prompt();
		 }
       }
       return 0;
}

