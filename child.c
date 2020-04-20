#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
	//printf("child process..\n");
	printf("child process.. argc %d\n",argc);
	for(int i = 0 ; i < argc; i++){
		printf("%d : %s \n",i,argv[i]);
	}
	
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	
	if (argc == 1)	{
		printf("usage: getenv env_vars ... \n");
		return 0;
	} else {
		
		for (i = 0 ; i < argc-1 ; i++) {
			env = getenv(argv[i+1]);
			printf("%s=%s\n", argv[i+1], env);
			for (j=0,str=env; ;str= NULL,j++) {
				tok[j] = strtok_r(str, ":", &saveptr);
				if (tok[j] == NULL) break;
				printf("\t%s\n", tok[j]);
			}
			printf("***---------------------***\n");
		}
	}
	return 0;
}



//TODO LIST

//1. 화이팅 ✅

//2. 우선 env을 가져와서 null이라면  ✅

//3. bin의 명령어를 실행시켜보자. ✅