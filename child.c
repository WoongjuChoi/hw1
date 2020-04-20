#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;


int functionENV(int argc, char * argv[])
{
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	if (argc == 1)	{
		//printf("usage: getenv env_vars ... \n");
		return -1;
	} else {
		for (i = 0 ; i < argc-1 ; i++) {
			env = getenv(argv[i+1]);
			if(env == NULL)
				return -1;
			printf("%s=%s\n", argv[i+1], env);
			for (j=0,str=env; ;str= NULL,j++) {
				tok[j] = strtok_r(str, ":", &saveptr);
				if (tok[j] == NULL) break;
				printf("\t%s\n", tok[j]);
			}
			printf("ENV END ---------------------\n");
		}
	}
	return 0;
}

int functionBasic(int argc, char **argv)
{
	if(argc==1)
		return -1;
	
	char* path = (char*)malloc(sizeof(char)*1000);
	strcpy(path,"/bin/");
	strcat(path,argv[1]);
	
	// for(int i = 2; i < argc;i++){
	// 	strcat(path,argv[i]);
	// }
	
	printf("finall path: %s\n",path);
	printf("argv => \n");
	for(int i = 2; i < argc; i++){
		printf("%s\n",argv[i]);
	}
	argv[argc] = NULL; //끝을 알림.

    if(execve(path, argv+1,environ) == -1) {
        fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
        return -1;
    }

    return 0;
}

int functionPATH(int argc,char **argv){
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	
	
	// char **new_argv = (char**)(malloc(sizeof(char*)*(argc)));
	
	// strcpy(new_argv[0],argv[0]);
	// for(int k=2; k <argc; k++){
	// 	strcpy(new_argv[k-1],argv[k]);
	// }
	
	printf("new argv\n");
	for(int k = 0 ; k < argc -1 ; k++){
		printf("%s\n",new_argv[k]);
	}
	
	if (argc == 1)	{
		//printf("usage: getenv env_vars ... \n");
		return -1;
	} else {
		env = getenv("PATH");
		if(env == NULL)
			return -1;
		printf("%s=%s\n", argv[i+1], env);
		for (j=0,str=env; ;str= NULL,j++) {
			tok[j] = strtok_r(str, ":", &saveptr);
			if (tok[j] == NULL) break;
			printf("PATH : \t%s\n", tok[j]);
			
			strcat(tok[j],"/");
			strcat(tok[j],argv[1]);
			if(argc == 2)
				execv(tok[j],argv+2);
			else
				execv(tok[j],argv+2);
		}
		
	}
	return 0;
}

int main(int argc,char **argv){
	//printf("child process..\n");
	printf("child process.. argc %d\n",argc);
	for(int i = 0 ; i < argc; i++){
		printf("%d : %s \n",i,argv[i]);
	}
	if(functionENV(argc,argv)==0){
		return 0;
	}
	
	if(functionBasic(argc,argv)==0){
		return 0;
	}
	printf("EXEC Basic command\n");
	if(functionPATH(argc,argv)==0){
		return 0;
	}
	
	return -1;
}



//TODO LIST

//1. 화이팅 ✅

//2. 우선 env을 가져와서 null이라면  ✅

//3. bin의 명령어를 실행시켜보자. ✅

//4. 환경변수 전달 하기 ㅜㅜ

