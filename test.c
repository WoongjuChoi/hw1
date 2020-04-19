#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	printf(" pid test\nmy pid : %d\n",(int)getpid());

	pid_t pid=fork();
	if(pid ==-1){
		printf("fork error\n");

	}else if (pid ==0){
		printf("child process\n");
		printf("child  pid : %d\n",pid);
	}else{
		printf("parent process\n");
		printf("parent  pid : %d\n",pid);
		

	}
	return 0;


	

}
