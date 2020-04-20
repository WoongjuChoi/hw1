#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_PATH 100
#define LF 10

int print_promt()
{
	// 100바이트를 동적으로 할당!
	char *buffer = (char *)malloc(MAX_PATH);
	//getcwd(버퍼의 절대주소, 버퍼의 크기) => 작업디렉토리 반환
	char *value = (char *)getcwd(buffer,MAX_PATH);

	if(value !=0)// value에 값이 할당되어있다면
		fprintf(stdout,"GunwooShell:%s>",buffer);
	
	//동적 메모리는 항상 까먹지 말고 반환합시다.
	free(buffer);

	return 0;
}

int main()
{
	char c;
    	printf("Welcome to GunwooShell, [Press Enter]");
	while( ( c=getchar() ) != EOF )
		if(c==LF)//LF=line feed의 약자로 줄바꿈으로 사용한다!
			fork();
			print_promt();
	return 0;
}
