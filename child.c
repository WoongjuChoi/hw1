#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
	printf("child process..\n");
	printf("argc %d\n",argc);
	for(int i = 0 ; i < argc; i++){
		printf("%d : %s \n",i,argv[i]);
	}
	return 0;
}