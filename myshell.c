#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fentl.h>
#include <unistd.h>
#include <signal.h>

//cd
void cd(char argc[])
{
	if(!strcmp(argc,"menu"))
	{
		printf("A.cd [FILE NAME]\n");
		printf("i FILENAME path move\n");
		printf("~ input -> home directory move\n"):
	}
	else{
		char *path; //파일의 이름을 넣어줄 포인터
		path = argc;

		if((path=(char*)getenv("HOME")) == NULL) //이후에 현재환경변수값을 불러오도록 fork한다.
			path=",";
		chdir(argc); //체인지 더 디렉토리로써 입력하였던 파일명이나 디렉토리로 이동. 이는 경로가 된다.
	}
}

//pwd
char* pwd()
{
	char *buf, *path;  //경로를 저장할 변수
	path = (char *)malloc(1024); //포인터형이므로 동적할당.
	getcwd(path,1024);	//경로를 호출하는 시스템콜 호출	
	printf(" %d\n", path);
	return path;
}

//cat
void cat(char argv[])
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
















