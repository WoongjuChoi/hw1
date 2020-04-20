#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *value;
	value = getenv("$myPath");

	printf("%s\n", value);

	return 0;
}
