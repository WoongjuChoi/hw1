#include<stdio.h>  //fprintf,setbuf,fgets
#include<stdlib.h> //malloc,free,getenv
#include<unistd.h> //getcwd,execve
#include<string.h> //strtok,strcmp,strcat,memset
#include<sys/wait.h> //wait
#define MAX_PATH 100  //버퍼의 크기
int print_prompt(){   //프롬프트 
	char *buffer =(char *)malloc(MAX_PATH);//버퍼의크기할당
	char *value=(char*)getcwd(buffer,MAX_PATH);//현재디렉토리의 경로
       	if(value !=0){ //getcwd함수 실패시 NULL
		fprintf(stdout,"shell:%s>",buffer); 
	}
	free(buffer); //동적으로 할당된 메모리 해제
        return 0;
}

int main(int argc,char *argv[],char *envp[]){
       char c;
       char cmd[80]; //입력받을 문자열
       char *vecl[10]; //execve함수 및 아래의 명령어 실행시 사용
       setbuf(stdout,NULL);
       print_prompt();
       while(fgets(cmd,80,stdin)!=NULL){//문자열 입력
	       int i=0;
	       cmd[strlen(cmd)-1]='\0'; 
	       memset(vecl,0x00,sizeof(vecl)); //vecl초기화
	       char *token;
	       token=strtok(cmd,"");//문자열 파싱
	       while(token){
		    vecl[i]=token;  //vecl배열에 할당
		    token=strtok(NULL,"");
		    i++;
		  }
             if(!strcmp(vecl[0],"quit")){//quit명령어 구현
		     exit(1);
		    }

             if(fork()==0){ //자식프로세스
	         if((!strcmp(vecl[0],"ls"))|(!strcmp(vecl[0],"cat"))|(!strcmp(vecl[0],"pwd"))){  //ls,cat,pwd명령어 구현
		     char path[100]="/bin/";  //bin 디렉토리
		     strcat(path,vecl[0]);
		     execve(path,vecl,envp);  //프로그램 실행
		  }
		 if(!strcmp(vecl[0],"cd")){ //cd명령어 구현
	             char *wrd;
		     char *context;
		     const char *delim="cd ";
		     wrd=strtok_r(vecl[0],delim,&context); //cd명령어를 제외한 문자열 구하기
		     char *n_path;
		     char *cdbuffer=(char *)malloc(MAX_PATH);
		 
		     if(wrd==NULL){ //cd명령어뿐
			     chdir(getenv("HOME")); //home디렉토리로 변경
			     n_path=(char *)getcwd(cdbuffer,MAX_PATH);
			     fprintf(stdout,"dir:%s\n",cdbuffer);
		      }
		      else{    //cd명령어 뒤에 다른 문자열 존재
			      chdir(getenv(wrd));   //해당 문자열 디렉토리로 변경
			      n_path=(char *)getcwd(cdbuffer,MAX_PATH);
		              fprintf(stdout,"ndir:%s\n",cdbuffer);
			  }
			free(cdbuffer);   
		   }
		     exit(0);
	     }
	     else{  //부모프로세스
		     wait(0); //자식프로세스 종료까지 대기
		     print_prompt();
		 }
       }
       return 0;
}

