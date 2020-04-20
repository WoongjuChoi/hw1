#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER 100

int main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	char file_name[BUFFER];
	char *fArr[20] = {NULL, };
	char path[BUFFER];
	

	printf("********************hw1*******************\n");

	while(1){

		printf("SiSH..%s$", argv[0]);//현재 경로 출력
		fgets(file_name, BUFFER, stdin);//사용자에게 입력받음
		if ((strcmp(file_name, "\n")==0))//공백 입력시 다시 입력받음
			continue;

		int i = 0;
		char *ptr = strtok(file_name," ");//입력을 공백 기준으로 구분
		
		while(ptr != NULL){//공백을 기준으로  구분하여 저장
			fArr[i] = ptr;
			i++;

			ptr = strtok(NULL, " ");
		}

		pid = fork();
		if (pid == -1){//부모 프로세스
			perror("fork error");
			return 0;
		}
		else if(pid == 0){//자식 프로세스
			if (strcmp(fArr[0], "quit")==0){//"quit"을 입력받았을 때 종료
				exit(0);
			}
			else if(strcmp(file_name, "ls\n")==0){//"ls"를 입력받으면 ls 실행
				execlp("/bin/ls","ls",NULL);
				exit(0);
			}
			else if(strcmp(fArr[0], "cd")==0){ //디렉토리 변경(동작 안함)
				char cPath[BUFFER], cdPath[BUFFER];
				getcwd(cPath, BUFFER);
				strcat(cdPath,"/");
				strcat(cdPath,fArr[1]);
				int cDir = chdir(cdPath);

				if(cDir == -1)//변경 안될때 에러 발생
					perror("directory change failed");
				exit(0);
			}
			else if(strcmp(file_name, "pwd\n")==0){//pwd 구현
				getcwd(path, BUFFER); //현재 경로
 			               if(path ==  NULL){ //경로의 길이가 psth의 길이보다 길면 출력 후 종료
                        			perror("current working directory get error");
						exit(0);
					}
				printf("%s\n", path);//경로 출력
				exit(0);
			}
			else{
				char *fPath = strtok(argv[0], " .:"); //파일 실행하는 부분(동작안힘)

				while(fPath != NULL){
					fPath = strtok(NULL," .:");
				}
				strcat(fPath, fArr[0]);
				
				char *argv[] = {fArr[0]};

				execve(fPath, argv, NULL);
				
				exit(0);
			}
		}
		else{
			wait(0);
		}
		
		if(strcmp(file_name, "quit\n")==0)//반복문 종료
			break;
	}
	printf("\nhw1.c end\n");
	return 0;
}
