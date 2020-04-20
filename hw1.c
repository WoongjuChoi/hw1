#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void  exec_process(char *path,char *argv[]){ //exec 실행 함수

        int f;
	char currentPath[200];
        do {
		strcpy(currentPath,path);
                strcat(currentPath,"/");
                strcat(currentPath,argv[0]);
                strcat(currentPath,"");  
		f=execv(currentPath,argv);
                path=strtok(NULL,":");
	
               }while(f==-1 && path !=NULL);

}

/*
void current_time(){ //미구현
	char abc[100];
	strcpy(abc,getenv("TIME"));
	printf("%s",abc);



}*/

 int main(int argc,char *argv[]){

	char input[200];    //사용자 입력
	char copyPath[200]; //환경변수 복사
   
	char *inputArgv[200]; //입력을 공백 단위로 잘라서 저장
        pid_t pid; //프로세스 아이디
	char *eachPath; //현재 사용하는 환경변수 포인터


	

	while(1){
		printf("JinHoShell#");
		char *pwd;
		char *user;
		pwd=getenv("PWD");//cd 명령어 실행이후 값이 바뀌지않음
		user=getenv("USER");
		printf("%s#",user);
		printf("%s>>",pwd);
		fgets(input,sizeof(input),stdin);  //사용자 입력

		if(input[0]=='\n'||input[0]==' ') //엔터 또는 스페이스바 입력시
			continue;
		inputArgv[0] = strtok(input," ");


		int i =0;



		do{
			i++;
			inputArgv[i]=strtok(NULL," "); //공백으로 분리 
			}while(inputArgv[i]);
		inputArgv[i-1]=strtok(inputArgv[i-1],"\n");

		if(strcmp(inputArgv[0],"quit")==0){
			printf("program quit\n ");
			return 0;
		} else if(strcmp(inputArgv[0],"cd")==0){ //cd 명령어 구현
			chdir(inputArgv[1]);
		}


		
 		 strcpy(copyPath,getenv("PATH"));
       		 eachPath=strtok(copyPath,":");



		 pid=fork();
		 if(pid ==-1){
			 printf("fork error\n");
		 }
		 else if (pid ==0){
			 //child process
			exec_process(eachPath,inputArgv);
			 exit(0);
		 }
		 else{
			 //parent process 
			 wait(0);
		 }








	}
	return 0;
}






	
