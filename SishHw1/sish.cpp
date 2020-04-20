#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream> // cpp
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	pid_t  pid;

	while(1)
	{
		pid = fork();
		
		if(pid == -1) // fail 
		{
			perror("fork error");
			return 0;
		}
		
		else if(pid == 0) // child
		{
			vector<string> v;
			v.push_back("./");
			char arr[50];
			cin << arr;
			v.push_back(arr);


			exit(0);

		}

		else // parent
		{
			wait(0);
		}

	}
	return 0;
}
