#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define ARGNUM 10 // 실행인자를 10개까지 받을 수 있다!

int main(void)
{
	char buf[300];	//입력을 받을 버퍼
	char *arg[ARGNUM];	// 입력에서 받은 인자를 넣는 곳:
	char *str;	//입력을 인자모양으로 잘라서 담는 곳!
	char *save;
	int argv;	//arg의 index

	static const char tok[] = " \t\n"; // 공백,탭,개행으로 자름
	char name[256]; //현재 디렉토리를 담을 변수
	int pid; // fork로 인한 프로세스id구분을 위한 변수
	
	system("clear");// 깔끔하게 지우고간다.
	puts("Welcome to Gunwoo's Shell![quit to escape] ");
	for( ; ;){
		getcwd(name,256); // name 배열에 현재 디렉토리저장
		printf("[Gunwoo@%s] @",name);//프롬프트 출력부
		fgets(buf,sizeof(buf),stdin);//buf에 입력받기
		argv=0; //현재 인자0
		//입력을 tok로 잘라 str에 넣고 각각접근하자.
                str = strtok_r(buf,tok,&save);

		/*==================================================*/
		//	input을 인자에 맞게 자르는 part
		/*==================================================*/
		while(str !=NULL)
		{
			arg[argv++] = str;
			//다음 입력조각을 str에 저장
			str = strtok_r(NULL,tok,&save);
		}
		//arg의 마지막인덱스에 0 대입
		arg[argv] = (char *)0;


		/*==================================================*/
		//	인자에 해당하는 실행 part
		/*=================================================*/
		// 쉘종료 part
		if(strcmp(arg[0],"quit")==0)
			break;
		// fork
		if( (pid=fork() ) == -1) 
			puts("에러 발생!");
		else if(pid != 0)	//부모 프로세스!
			pid = wait(NULL);
		else	// 자식 프로세스!
			execvp(arg[0],arg);
	}
	return 0;
}
