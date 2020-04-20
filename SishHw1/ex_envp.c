#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <environment key> \n", argv[0]);
		return 1;
	}

	char *env = getenv(argv[1]);
	if(env)
	{
		printf("%s's value is %s\n", argv[1], env);
	}
	else 
	{
		printf("%s is not existed\n", argv[1]);
	}
	return 0;
}
