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
			//printf("ENV END ---------------------\n");
		}
	}
	return 0;
}

// int functionBasic(int argc, char **argv)
// {
// 	if(argc==1)
// 		return -1;
	
// 	char* path = (char*)malloc(sizeof(char)*1000);
// 	strcpy(path,"/bin/");
// 	strcat(path,argv[1]);
	
// 	// for(int i = 2; i < argc;i++){
// 	// 	strcat(path,argv[i]);
// 	// }
	
// 	//printf("finall path: %s\n",path);
// 	//printf("argv => \n");
// 	// for(int i = 2; i < argc; i++){
// 	// 	printf("%s\n",argv[i]);
// 	// }
// 	argv[argc] = NULL; //끝을 알림.

//     if(execve(path, argv+1,environ) == -1) {
//         //fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
// 		free(path);
//         return -1;
//     }
// 	free(path);
//     return 0;
// }

int functionPATH(int argc,char **argv){
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	
	if (argc == 1)	{
		//printf("usage: getenv env_vars ... \n");
		return -1;
	} else {
		
		//절대경로라면 그대로 실행
		if(argv[1][0]=='/'){
			if(execv(argv[1],argv+1)==0){
				return 0;
			}
		}
		char* path = (char*)malloc(sizeof(char)*1000);
		//그냥 파일만 있다라면 > 현재 디렉터리에서 실행해봄
		char *pwd = getenv("PWD");
		//printf("pwd : %s \n",pwd);
		strcpy(path,pwd);
		strcat(path,"/");
		strcat(path,argv[1]);
		if(execv(path,argv+1)==0){
			free(path);
			return 0;
		}
		
		//그대도 실패하면 모든 환경변수에 등록된 PATH 탐색
		env = getenv("PATH");
		if(env == NULL)
			return -1;
		//printf("%s=%s\n","PATH", env);
		
		for (j=0,str=env; ;str= NULL,j++) {
			tok[j] = strtok_r(str, ":", &saveptr);
			if (tok[j] == NULL) break;
			//printf("PATH : \t%s\n", tok[j]);
			strcpy(path,tok[j]);
			strcat(path,"/");
			strcat(path,argv[1]);
			//printf("final route %s\n",path);
			if(execv(path,argv+1)==0){
				free(path);
				return 0;
			}
		}
		free(path);
	}
	return -1;
}

int main(int argc,char **argv){
	//printf("child process..\n");
	// printf("child process.. argc %d\n",argc);
	// for(int i = 0 ; i < argc; i++){
	// 	printf("%d : %s \n",i,argv[i]);
	// }
	if(functionENV(argc,argv)==0){
		return 0;
	}
	// if(functionBasic(argc,argv)==0){
	// 	return 0;
	// }
	if(functionPATH(argc,argv)==0){
		return 0;
	}
	printf("myshell %s command not found\n",argv[1]);
	
	return -1;
}



//TODO LIST

//1. 화이팅 ✅

//2. 우선 env을 가져와서 null이라면  ✅

//3. bin의 명령어를 실행시켜보자. ✅

//4. 환경변수 전달 하기 ㅜㅜ

// export PATH=$PATH:/workspace/OSLecture/hw1master

//   /workspace/OSLecture/hw1master/argv
