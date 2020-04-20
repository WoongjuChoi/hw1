
# Project SimpleShell

## myshell program


# 1. install

```js

first execution:

make

next execution:

make build

```

# 2. requirement env

```js
Linux Kernel version : Linux version 4.4.0-1104-aws (buildd@lgw01-amd64-036) (gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.12) ) #115-Ub
untu SMP Mon Mar 2 06:35:35 UTC 2020

gcc   version : gcc version 9.1.0 (Ubuntu 9.1.0-2ubuntu2~18.04)

make  version : GNU Make 4.1
```

# 3. usage

-  execution file

```js


Example  C File  : argv.c

#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	printf("argv print .. \n");
	for(int i = 1 ; i < argc;i++){
		printf("%s\n",argv[i]);
	}
	return 0;
}

✅myshell:root:/workspace/OSLecture/hw1master#argv hello world
argv print ..
hello
world



Example execute file in PATH env 

✅myshell:root:/workspace/OSLecture/hw1master#argv hello world
argv print ..
hello
world
✅myshell:root:/workspace/OSLecture/hw1master#cd ../
✅myshell:root:/workspace/OSLecture#cd ../
✅myshell:root:/workspace#argv hello world
argv print ..
hello
world
```

- Exit 

```js
✅myshell:root:/workspace/OSLecture/hw1master#quit
MY SHELL EXIT THANKS..❤
make[1]: 디렉터리 '/workspace/OSLecture/hw1master' 나감
```

-   basic command

```js



✅myshell:root:/workspace/OSLecture/hw1master#ls
LICENSE  Makefile  README.md  argv  argv.c  child  child.c  fork.c  fork2.c  getenv  getenv.c  myshell  myshell.c  stat.c  test.c

✅myshell:root:/workspace/OSLecture/hw1master#ls -al
합계 116
drwxrwxr-x 3 root root  4096  4월 20 11:11 .
drwxr-xr-x 6 root root  4096  4월 20 00:03 ..
drwxrwxr-x 8 root root  4096  4월 20 10:47 .git
-rw-rw-r-- 1 root root  1078  4월 19 18:01 LICENSE
-rwxrwxr-- 1 root root   302  4월 20 10:04 Makefile
-rw-rw-r-- 1 root root  5178  4월 20 11:12 README.md
-rwxrwxr-x 1 root root  8296  4월 20 07:03 argv
-rwxrwxr-- 1 root root   173  4월 20 10:04 argv.c
-rwxrwxr-x 1 root root 12832  4월 20 11:11 child
-rwxrwxr-- 1 root root  2274  4월 20 10:04 child.c
-rw-rw-r-- 1 root root   456  4월 19 18:01 fork.c
-rw-rw-r-- 1 root root  1842  4월 19 18:01 fork2.c
-rwxrwxr-x 1 root root  8488  4월 20 05:30 getenv
-rw-rw-r-- 1 root root   551  4월 20 05:50 getenv.c
-rwxrwxr-x 1 root root 13288  4월 20 11:11 myshell
-rwxrwxr-- 1 root root  2294  4월 20 10:26 myshell.c
-rw-rw-r-- 1 root root   402  4월 20 10:04 stat.c
-rwxrwxr-- 1 root root   956  4월 20 10:04 test.c



✅myshell:root:/workspace/OSLecture/hw1master#clear



✅myshell:root:/workspace/OSLecture/hw1master#mkdir ./test

✅myshell:root:/workspace/OSLecture/hw1master#ls
LICENSE  Makefile  README.md  argv  argv.c  child  child.c  fork.c  fork2.c  getenv  getenv.c  myshell  myshell.c  stat.c  test  test.c

✅myshell:root:/workspace/OSLecture/hw1master#rm -rf ./test

✅myshell:root:/workspace/OSLecture/hw1master#ls
LICENSE  Makefile  README.md  argv  argv.c  child  child.c  fork.c  fork2.c  getenv  getenv.c  myshell  myshell.c  stat.c  test.c

```

-   getenv

```

✅myshell:root:/workspace/OSLecture/hw1master#PATH
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
        /usr/local/sbin
        /usr/local/bin
        /usr/sbin
        /usr/bin
        /sbin
        /bin
        /usr/games
        /usr/local/games
		
		
✅myshell:root:/workspace/OSLecture/hw1master#SSH_TTY
SSH_TTY=/dev/pts/2
        /dev/pts/2

✅myshell:root:/workspace/OSLecture/hw1master#PWD
PWD=/workspace/OSLecture/hw1master
        /workspace/OSLecture/hw1master

```


# 프로그램 코드 설명

## 1. 부모 프로세스

```c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
char cwd[1024]; //실시간을 변경되는 현재 디렉터리 저장
char cwd_init[1024]; // 초기 디렉터리 > 자식 파일
char CHILD_PATH[1024];
//명령어를 파싱한다 -> new_argv 문자열 배열(1번부터)에 각각 담는다. (뛰어쓰기,개행,,,탭 구분)
void InputParsing(char *command, char **new_argv)
{
    int j;
    char *str, *next_ptr;
    for (int i = 0; i < 100; i++){
        new_argv[i] = NULL;
    }
    for (j = 1, str = command;; str = NULL, j++){
        new_argv[j] = strtok_r(str," ,\t\n", &next_ptr);
        if (new_argv[j] == NULL || strcmp(new_argv[j],"\n")==0)
            break;
    }
    return;
}
void init(){
	getcwd(cwd_init, sizeof(cwd_init));
	strcpy(CHILD_PATH,cwd_init);
	strcat(CHILD_PATH,"/child");
	return;
}


int main(int argc, char *argv[])
{
	puts("myshell powered by DOSIMPACT");
	init();
	pid_t pid;
	int i;
	char userInput[100];
	//----------------------------------------------
	char* saveptr;
    char* new_argv[100] = {
        NULL,
    };
	char* username = getenv("USER");
	
	while(1){
		//char* pwd = getenv("PWD");
		getcwd(cwd, sizeof(cwd));
		printf("✅myshell:%s:%s#",username,cwd);
		fgets(userInput,sizeof(userInput),stdin);
		
		if(strcmp(userInput,"quit\n")==0){
			puts("MY SHELL EXIT THANKS..❤");
			break;
		}
		if(strcmp(userInput,"\n")==0){
			continue;
		}


		InputParsing(userInput, new_argv);
		new_argv[0] = argv[0];
		if(strcmp(new_argv[1],"cd")==0){
			chdir(new_argv[2]) == 0;
			continue;
		}
		pid = fork();
		if(pid == -1){
			perror("ERROR: fork fail");
		}
		else if(pid == 0){
			// char resolved_path[1000];
			// realpath(argv[0], resolved_path);
			// printf("real path %s",resolved_path);
			execve(CHILD_PATH,new_argv,environ);
			exit(0);
		}else{
			wait(0);
		}
		
	}

	return 0;
}



```

## 2. 자식 프로세스


```c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int functionENV(int argc, char * argv[])
{
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	if (argc == 1)	{
		//printf("usage: getenv env_vars ... \n");
		return -1;
	} else {
		for (i = 0 ; i < argc-1 ; i++) {
			env = getenv(argv[i+1]);
			if(env == NULL)
				return -1;
			printf("%s=%s\n", argv[i+1], env);
			for (j=0,str=env; ;str= NULL,j++) {
				tok[j] = strtok_r(str, ":", &saveptr);
				if (tok[j] == NULL) break;
				printf("\t%s\n", tok[j]);
			}
		}
	}
	return 0;
}

int functionPATH(int argc,char **argv){
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	
	if (argc == 1)	{
		//printf("usage: getenv env_vars ... \n");
		return -1;
	} else {
		
		//절대경로라면 그대로 실행
		if(argv[1][0]=='/'){
			if(execv(argv[1],argv+1)==0){
				return 0;
			}
		}
		char* path = (char*)malloc(sizeof(char)*1000);
		//그냥 파일만 있다라면 > 현재 디렉터리에서 실행해봄
		char *pwd = getenv("PWD");
		//printf("pwd : %s \n",pwd);
		strcpy(path,pwd);
		strcat(path,"/");
		strcat(path,argv[1]);
		if(execv(path,argv+1)==0){
			free(path);
			return 0;
		}
		
		//그대도 실패하면 모든 환경변수에 등록된 PATH 탐색
		env = getenv("PATH");
		if(env == NULL)
			return -1;
		//printf("%s=%s\n","PATH", env);
		
		for (j=0,str=env; ;str= NULL,j++) {
			tok[j] = strtok_r(str, ":", &saveptr);
			if (tok[j] == NULL) break;
			//printf("PATH : \t%s\n", tok[j]);
			strcpy(path,tok[j]);
			strcat(path,"/");
			strcat(path,argv[1]);
			//printf("final route %s\n",path);
			if(execv(path,argv+1)==0){
				free(path);
				return 0;
			}
		}
		free(path);
	}
	return -1;
}

int main(int argc,char **argv){

	if(functionENV(argc,argv)==0){
		return 0;
	}

	if(functionPATH(argc,argv)==0){
		return 0;
	}
	printf("myshell %s command not found😢\n",argv[1]);
	
	return -1;
}





```


# 프로그램에 사용된 코드 스니펫


## 0. 매개변수 출력 


```c
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	printf("argv print .. \n");
	for(int i = 1 ; i < argc;i++){
		printf("%s\n",argv[i]);
	}
	return 0;
}

```

## 1. fork example01

```c


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// getpid() 현재 pid, getppid() 부모 pid
// pid_t = cpid = fork() > 편안하게 프로세스의 메타정보 > 0이면 자식 프로세스이다. 0이 아니면 부모 프로세스이다. 근데, 그  0아닌 값이 자식 pid 이얌
int main()
{
    printf("start...\n");
    printf("pid: %u ppid:%u \n", getpid(), getppid());
    pid_t cpid = fork(); //부모는 1이상 값, 자식에게는 0, 으로 분기됨
                         //-1 이면 애러
    if (cpid == -1)
    {
        perror("error fork");
        return 1;
    }
    if (cpid > 0)
    { //getpid 부모 | getppid 자식
        printf("<parent> fork return value:%u\n", cpid);
        printf("<parent> pid:%d ppid:%d\n", getpid(), getppid());
        sleep(1);
    }
    else
    {
        printf("<child> fork return value:%u\n", cpid);
        printf("<child> pid:%d ppid:%d\n", getpid(), getppid());
    }
    return 0;
}
// getpid() 나의 프로세스
// getppid() 부모 프로세스
/*
pid_t cpid = fork();
*/
```


## 2. fork example02

- fork( ) 순간에 프로세스 분기가 일어난다.
- fork의 반환값으로 -1 ( 애러 ) 0 이면 자식 프로세스이라는 뜻 | 0이아니면 부모 프로세스임 근대 0아닌 그값이 자식 pid임
- getpid,getppid 로 내 pid, 부모 pid를 얻어올 수 있다.
- for문의 i 는 아래 예제와 같이 부모 프로세스에서 fork되는 순간의 값을 복사해 온다. 그리고 그 둘은 전혀 다른 메모리공간의 주소이다.
- wait를 통해 자식 프로세스가 exit (0) 까지 기다린다.



```c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    int i;
    for (i = 0; i < 10; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            return 0;
        }
        else if (pid == 0)
        {
            // child
            i = i + 2;
            printf("child process with pid %d (i: %d) -> parent : %d \n", getpid(), i, getppid());
            exit(0);
        }
        else
        {
            // parent
            printf("Parent -> %d Waiting...(i: %d) \n", getpid(), i);
            wait(0);
        }
    }
    return 0;
}
```

## 3 getenv.c


- 리눅스 시스템에는 환경변수가 있다. env라고 치면 나온다.
- 이 환경변수는 key,value로 이루어져 있다.
- 만약에 하나의 key에 여러값을 넣고 싶다라면 value를 : 로 구분해서 값을 넣어두었다.
  예) PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
  
  
- 아래 코드는 환경변수를 출력해주는 예제.
- argc 인자값 개수, argv ( char포인터형 을 여러 개(배열) 받는다. )
- 참고) int arr[ ]로 int 형 배열을 매겨변수로 받을 수 있다. | char* argv 로 문자열 하나(사실 char포인터) 를 받을 수 있다. | char* argv[ ] 로 문자열 여러개를 받는다.
- 해당 인자값으로 getenv 결과값을 : 로 토크나이져 해서 출력

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * argv[])
{
    int i, j=0;
    char *env, *str;
    char *tok[100], *saveptr;

    if (argc == 1)  {
        printf("usage: getenv env_vars ... \n");
        return 0;
    } else {

        for (i = 0 ; i < argc-1 ; i++) {

            env = getenv(argv[i+1]);
            printf("%s=%s\n", argv[i+1], env);

            for (j=0,str=env; ;str= NULL,j++) {
                tok[j] = strtok_r(str, ":", &saveptr);
                if (tok[j] == NULL) break;
                printf("\t%s\n", tok[j]);
            }

            printf("***---------------------***\n");
        }

    }
    return 0;
}

```

## 4  strtok_r

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * argv[])
{
    int i, j=0;
    char *env, *str;
    char *tok[100], *saveptr;
    if (argc == 1)  {
        printf("usage: getenv env_vars ... \n");
        return 0;
    } else {
        for (i = 0 ; i < argc-1 ; i++) {


            env = getenv(argv[i+1]);
            printf("%s=%s\n", argv[i+1], env);


            for (j=0,str=env; ;str= NULL,j++) {
                tok[j] = strtok_r(str, ":", &saveptr);
                if (tok[j] == NULL) break;
                printf("\t%s\n", tok[j]);
            }

            printf("***---------------------***\n");
        }
    }
    return 0;
}
```

```c
#include <string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    char command[] = "ls -al a*";
    char *next_ptr;
    char *sArr[10] = {
        NULL,
    };
    char *str;
    int j = 0;
    // command 의 갯수와 , 그를 담는 문자열 배열
    for (j = 0, str = command;; str = NULL, j++)
    {
        sArr[j] = strtok_r(str, " ", &next_ptr);
        if (sArr[j] == NULL)
            break;
    }
    for (int i = 0; i < 10; i++)
    {
        if (sArr[i] != NULL)
            printf("%s\n", sArr[i]);
    }
}
```

```
파라미터
str
    - delimiter단위로 분리할 문자열.
    - NULL이면 saveptr 변수에서 저장하고 있던 이전에 호출한 위치 다음부터 분리작업을 진행합니다.
  ※주의 : str문자열은 변경이 일어나기 때문에 원본 문자열을 보존하려면 
          임시변수에 복사한 후 임시변수를 사용하기 바랍니다.
delim
    - 문자열을 분리할 delimiter 문자들. delim에 포함된 아무 문자라도 만나면 분리함.
saveptr
    - 다음처리를 위한 위치를 저장하는 pointer
    - 이 변수는 직접 handling하지 않습니다
 
RETURN
NULL 아님
    - 정상적으로 delimiter로 분리하였으며, 분리된 문자열의 시작 pointer를 return합니다.
    
NULL
    - 분리할 데이터가 더 이상없습니다.
 
활용 예제
 ```
 
 ```c
#include <string.h>
#include <stdio.h>
/* /또는 - 또는 : 또는 space를 delimiter로 사용합니다. */
#define DELIM_CHARS     "/-: "
int main(int argc, char **argv)
{
    char time[1024] = "2017-02-12 10:25:30";
    char *ret_ptr;
    char *next_ptr;
    printf("time : [%s]\n", time);

    ret_ptr = strtok_r(time, DELIM_CHARS, &next_ptr);
    while(ret_ptr) {
        printf("ret_ptr = [%s]\n", ret_ptr);
        ret_ptr = strtok_r(NULL, DELIM_CHARS, &next_ptr);
    }

    return 0;
}
```
결과:
time : [2017-02-12 10:25:30]
ret_ptr = [2017]
ret_ptr = [02]
ret_ptr = [12]
ret_ptr = [10]
ret_ptr = [25]
ret_ptr = [30

출처: [https://www.it-note.kr/86](https://www.it-note.kr/86) [IT 개발자 Note]

## 4.2 C언어 문자열 연결

```c
#define _CRT_SECURE_NO_WARNINGS // strcpy 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h> // strcat 함수가 선언된 헤더 파일
#include <stdlib.h> // malloc, free 함수가 선언된 헤더 파일
int main()
{
    char *s1 = "world";                           // 문자열 포인터
    char *s2 = (char *)malloc(sizeof(char) * 20); // char 20개 크기만큼 동적 메모리 할당
    strcpy(s2, "Hello"); // s2에 Hello 문자열 복사
    strcat(s2, " ");
    strcat(s2, s1); // s2 뒤에 s1을 붙임
    printf("%s\n", s2); // Helloworld
    free(s2); // 동적 메모리 해제
    return 0;
}
```


## 5. execv

```c
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char **argv)
{
    printf("argument count is %d\n", argc);
 
    int i=0;
    printf("arugment list\n");
    for(i=0; i< argc; i++)
    {
        printf("<%d>: %s\n", i, argv[i]);
    }
 
    return 0;
}
```


```c

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    if(argc == 1)
    {
        printf("Usage: %s <exec path> , [arg0, arg1, arg2, ...]\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        return 1;
    }
    if(pid == 0)
    {
        wait(0);
    }
    else
    {
        execv(argv[1],argv+1);
        return 0;
    }
    return 0;
}
```

## 6 . make, makefile 리눅스 리눅스 c언어 makefile


- make 명령어로 컴파일을 실행 ( make는 파일 관리 유틸리티 이다. )
- makefile( 기술파일 ) 에 적힌대로 컴파일러에게 명령하여 shell 명령이 순차적으로 실행

- 기존의 컴파일 과정이 여기서는 그리 귀찮지 않습니다. 모든 c파일을 각각 컴파일 해도 3번만 명령해 주면 되니까요. 하지만 만약 하나의 실행파일을 생성하는데 필요한 c파일이 1000개라면..?? 1000개의 명령어가 필요합니다. 이러한 상황을 해결해 주는 것이 바로 make 와 Makefile입니다!

Makefile은 다음과 같은 구조를 가집니다.

- 목적파일(Target) : 명령어가 수행되어 나온 결과를 저장할 파일
- 의존성(Dependency) : 목적파일을 만들기 위해 필요한 재료
- 명령어(Command) : 실행 되어야 할 명령어들
- 매크로(macro) : 코드를 단순화 시키기 위한 방법


```
CC = gcc
TARGET_MAIN = myshell
TARGET_CHILD = child

$(TARGET_MAIN) : 
		$(CC) -o $(TARGET_MAIN) $(TARGET_MAIN).c && $(CC) -o $(TARGET_CHILD) $(TARGET_CHILD).c
		
clean	:
		rm $(TARGET_MAIN) && rm $(TARGET_CHILD)
				
start	:$(TARGET_MAIN)
		./$(TARGET_MAIN)

build	:
		make clean && make && make start
```

## 7. ls 명령어 그대로 실행하는 프로그램

```
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    char **new_argv;
    char command[]  = "ls";
    int  idx;
    new_argv = (char **)malloc(sizeof(char *) * (argc + 1));

    /* 명령어를 ls로 변경 */
    new_argv[0] = command;

    /* command line으로 넘어온 parameter를 그대로 사용 */
    for(idx = 1; idx < argc; idx++) {
        new_argv[idx] = argv[idx];
    }

    /* argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 파라미터의 끝을 의미함 */
    new_argv[argc] = NULL;
    if(execv("/usr/bin/ls", new_argv) == -1) {
        fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
        return 1;
    }


    /* ls 명령어 binary로 실행로직이 교체되었으므로 이후의 로직은 절대 실행되지 않습니다. */
    printf("이곳이 이제 ls 명령어라 이 라인은 출력이 되지 않습니다.\n");
    return 0;
}
--------------------------------------------------------------
실행방법
sample1 -al <enter>
결과는 ls -al 한 것과 같음.
```


# 2020_os_hw1
HW1: Simple MyShell

Operating Systems & Adv. Mobile project HW1: simple Shell (SiSH)

**Updated! Due by April 20th**

Introduction
Shell is a small program that allows a user to directly interact with your operating system. A user can command (give orders) to run program through shell. To do that, shell takes input string from a user, and make it run. When the specified program completes its execution, the shell takes another input to run another program.

In this homework (programming assignment), you will have to write a small shell program.

Shell usually works with low-level OS functions such as system calls. You may look into detailed usage of the following system calls: fork, execve, wait. Fork is a system call that creates another user process; it actually creates a copy of the caller. Then, the process becomes two different processes, return with different values. For parent process (that creates the child), fork() call returns with some number, that is the process id of the child process. For child process, fork() call returns with zero. Note that both (parent and the child) uses the same code base.

Execve is another important OS function that change the process into another process. The call takes the filename as argument, that the user wants to execute. The call discards the current program context (address space, changed memory values, register values, etc.), and loads the specified program into the memory. It then begins execution from the very beginning point of the program. Now that you can run another program that you want to execute in the child process.

Finally, wait() is a system call that stops the execution of the parent process. The parent process has to wait until the child completes its execution in order to gather and clean up the resources used by the children. The wait() call implements such waiting.

## You may further look into the following APIs: strtok_r, getenv.

# Specific requirements
1.	(optional) make & compile: write a makefile that compiles your code. I will just type make on the terminal.
1.	Start of SiSH: by entering the executable filename, your shell starts.
1.	End of Sish: SiSH finishes execution when it gets ‘quit’ string from the user.
1.	Operation of SiSH:
    1.	Input: takes program name as input string
    1.	Execution: it has to execute every single executable program in the filesystem, if it has proper privilege
    1.	Execution path: to simplify (contract) the filename (full path beginning with ‘/’), SiSH should look into directories, in PATH environment variable.
    1.	PATH environment variable holds the ‘:’-separated string, that specifies multiple locations in the filesystem.
    1.	During the execution of the user-input program, shell should not be active.
    1.	Repetition: When the given program completes its execution, it receives the next input string, to run another program.
1.	(optional) You can specify different shell prompt using getenv function. (e.g. your current working directory (PWD, TIME, USER, etc.)
1.	(optional) You can take additional input parameters for the executing program, and pass them to the created process. Please find manual pages of execve system call.
1.	Document:
    1.	You should include some report for your code project, hw, etc.
    1.	The report should include general/brief introduction to your program.
    1.	The report should include specific instruction to make your program.
    1.	The report should include specific working example. (screen capture, whatever)
    1.	The report can include your personal ideas, feedback messages to me.
1.	Submission
    1.	You have five freedays. (for all projects, homework assignments)
    1.	Submit your code through github account, in **your own branch**.
    1.	Branch should be your student ID.
    1.	Test before push. Do not push the broken code in git.
1.	Evaluation
    1.	It’s better if your code is different from the others.
    1.	More functionalities, more error handling is better.

No restrictions on working environment, if it supports POSIX standard programming interface. However, I strongly recommend you to stick to assam server; you may have different working environment, according to the running platform (OS).

No copy allowed. Please push your code in github hw1, in different branches. Do not push your code to master branch! Note that you can look at others’ code, and vice versa.

Different code implies better evaluation. Enjoy your system-level programming!
