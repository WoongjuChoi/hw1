#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
int main(char *argv[]){
	int main(char *argv[]){}
	char* str[2];
	str[0]="vi";
	str[1]="fork.c";
	while(1){
	printf("input path:");
	strcat(str[0],str[1]);
	
	if(execve("/usr/local/bin/",str,NULL) ==-1)printf("no\n");
	
	}
}

