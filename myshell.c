#include <stdio.h> // printf() 
#include <string.h> // perror(), strlen() 
#include <unistd.h> // fork() 
#include <sys/wait.h> // waitpid() 
#include <time.h> // time(), localtime(), asctime() 
#include <stdlib.h> // exit() 
#define MAX 255 
 // print out prompt and get command string from user 
 void *prompt(char cBuf[]) { 
 	time_t rawtime; 
 	struct tm *timeinfo; 
 	char hBuf[MAX], uBuf[MAX], dBuf[MAX]; 
 	char *now; 
 	void *ret; 

 	time(&rawtime); // passed time from Jan 1, 1970 
 	timeinfo = localtime(&rawtime); // translate rawtime to struct tm type 
 	now = asctime(timeinfo); // convert to string format 
 	now[strlen(now)-1] = 0; // convert '\n' to null charactor 
 	gethostname(hBuf, MAX); // save hostname to hBuf 
 	getlogin_r(uBuf, MAX); // save username to uBuf 
 	getcwd(dBuf, MAX); // save directoryname to dBuf 
 	printf("[%s]%s@%s(%s)$ ", now, hBuf, uBuf, dBuf); // print out prompt 


 	// get command string and save return value to ret pointer variable. 

 	// if fgets fails, it returns NULL 

 	ret = fgets(cBuf, MAX, stdin); 


 	// convert '\n' to null charactor so that 

 	// it can be recognized as string 

 	if(cBuf[strlen(cBuf)-1] == '\n') 
 		cBuf[strlen(cBuf)-1] = 0; 
 	return ret; 
 } 
 int main() 
 {
 	char cBuf[MAX]; 
 	char *arg; 
 	pid_t pid; 
	int status; 
 	while(prompt(cBuf)) { // while successful input 

 		/* 

 			fork() is called once, returned twice. 

 			one for parent(return value = pid of child process), 

 			the other one for child(return value = 0) 

 		*/ 



 		// pid should be integer greater than or equeal to zero. 

 		if((pid = fork()) < 0) { 

 			perror("fork error"); 

 		} 

 		else if(pid == 0) { // children case 

   

 			// split command input string 
			// strtok() changes character which is same with delimeter 

 			// to null character and returns pointer to first character of 

 			// seperated string. 

 			strtok(cBuf, " "); 

 			arg = strtok(NULL, " "); // return null if no more possible seperation 
	 

   

 			// execlp() need program name for first parameter, 

 			// argument list until (char*) 0 for more than second parameter, 

 			// and execute that program. 

 			if(arg == NULL) // no argument 

 				execlp(cBuf, cBuf, (char*) 0); 

 			else { // one argument 

 				if(strcmp(cBuf, "cd") == 0) { 

 					chdir(arg); 

 					_exit(0); 

 				} 

 				else 

 					execlp(cBuf, cBuf, arg, (char*) 0); 
			} 
			perror("couldn't execute"); 

 		} 
   

 		// wait until spawned process finishes. 

 		waitpid(pid, &status, 0); 

 	} 

   

 	// termination when fgets returns null. 

 	exit(0); 
 } 
