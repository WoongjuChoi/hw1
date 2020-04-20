
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
