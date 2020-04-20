#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
char* tokens[1024];
int main() 
{
	char line[1024];
	printf("input: ");
	fgets(line, sizeof(line), stdin);

	int token_count = 0;
	tokens[token_count] = strtok(line, "  \n");
	
	while(tokens[token_count] != NULL && token_count < 1024)
	{
		tokens[++token_count] = strtok(NULL,"  \n");
	}

	printf("%s %s\n", tokens[0], tokens[1]);
	
}
