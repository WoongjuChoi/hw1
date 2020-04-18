#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fentl.h>
#include <unistd.h>
#include <signal.h>

//main
int main(int argc, char *argv[])
{
	char *cmp; //입력시 토큰 분리를 위한 변수
	char *input_tem[5];  //토큰 분리시 사용될 2차원 배열
	input_tem[2] = NULL;
	char input[20]; //쉘 시작시 프롬프트에 입력 받는 변수
	char *showp;
	int size;
	char *w[2]; //옵션을 주지 않았을 시에 처리해줄 변수
	signal(SIGINT,sig_quit); //signal setting, SIGINT, handling

	char *buf, *path;
	path = (char *)malloc(1024);
	getcwd(path, 1024);
	strcat(path,":");
	if(strcat(path,(char *)getenv("PATH")) == NULL) //getenv를 이용하여 환경변수 정보를 불러오되 strcat으로 정보를 이어주도록 함.
		perror("getenv error\n");
	if(setenv("PATH",path,1)) //여기서 초기 환경 변수 설정.
		perror("setenv error\n");
	if(fgets(input,20,stdin)==NULL) //입력데이터 수신
	{
		printf("\nexecute EOF\N");
		exit(1);
	}
	else if(strcmp(input,"exit\n") ==0) //exit를 입력했을때 종료.
	{
		printf("input exit\n");
		exit(1);
	}
	else if(!strcmp(input_tem[0],"myenv\n"))
	{
		myenv();
	}
	else if(!strcmp(input_tem[0],"cd")) //cd명령어
	{
		char qwe[20];
		char *w;
		strcpy(qwe,input_tem[1]); //마찬가지로 입력을 분리하였을 때에 마지막에 남을 개행을 제거해주도록 하여 커맨드만 남도록 한다.
		w=strtok(qwe,"\n");
		cd(w);
	}
	else if(!strcmp(input,"mypsw\n") ==0) 
	{
		printf("%s\n",mypwd());
	}
	else if(!strcmp(input_tem[0],"mycat"))
	{
		char qwe[20];
		char *w;
		char *chec=NULL;
		strcpy(qwe,input_tem[1]);
		w=strtok(qwe,"\n"); //두번째 입력되는 개행을 잘라주도록 하여 현재 개행이 문장형태로 이루어지게 됨
		if(input_tem[2]==NULL) //이때 입력했던 값이 2개냐, 3개냐에 따라 각기 다른 함수를 호출한다. 이는 옵션기능에 해당함.
			mycat(w);
}


//myenv
extern char **environ; //환경변수를 확장하여 호출하는 변수
void myenv()
{
	char **ex= environ; //값을 복사
	while(*ex){ //값이 정상적일때, 모든 환경변수값들을 호출해주도록 하였따.
		printf("%s\n",*ex);
		ex++;
	}
}

//cd
void cd(char argc[])
{
	if(!strcmp(argc,"menu"))
	{
		printf("A.cd [FILE NAME]\n");
	}
	else{
		char *path; //파일의 이름을 넣어줄 포인터
		path = argc;

		if((path=(char*)getenv("HOME")) == NULL) //이후에 현재환경변수값을 불러오도록 fork한다.
			path=",";
		chdir(argc); //체인지 더 디렉토리로써 입력하였던 파일명이나 디렉토리로 이동. 이는 경로가 된다.
	}
}

//mypwd
char* mypwd()
{
	char *buf, *path;  //경로를 저장할 변수
	path = (char *)malloc(1024); //포인터형이므로 동적할당.
	getcwd(path,1024);	//경로를 호출하는 시스템콜 호출	
	printf(" %d\n", path);
	return path;
}

//mycat
void mycat(char argv[])
{
	if(!strcmp(argv,"menu"))
	{
		printf("cat [FILE NAME]\n")
	}
	else{
		FILE *fp;
		int c;
		char buffer[buf];
		fp = fopen(argv,"r");
		if(fp != NULL)
		{
			while(fgets(buffer,buf,fp) !=NULL) //기존에 입력되어있는 파일의 내용을 한번에 받아서 출력
				printf("%s",buffer);
		}
		else
		{
			printf("cat error\n");
			return 0;
		}

		fclose(fp);
	}
}
















