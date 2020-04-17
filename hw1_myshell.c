#include <stdio.h>
#include <unistd.h>  // getcwd(), execve()
#include <stdlib.h>  // malloc(), getenv()
#include <string.h>  //strtok_r(), strcmp()
#include <errno.h>  //perror()
#include <sys/wait.h> //waitpid()


#define MAX_PATH  255
#define DELIM_CHAR  ": \n"


void prompt_line()
{
	char *buffer = (char *) malloc(MAX_PATH);
	getcwd (buffer,MAX_PATH);

	printf("32152428_shinjeonghwan:%s$", buffer);
	free(buffer);
}



extern char **environ;

int main()
{
	pid_t pid;

	char input_str[100];
	char *input_str_tok;
	char *save_ptr;
	char *options[10] = {NULL};


	char *getPATH;
	char **getPATH_tok = (char **) malloc(MAX_PATH);
	getPATH = getenv("PATH");
	char *save_ptr2;

	char *PATH_tok = malloc(sizeof(char)*10);

	int status;

	char wd[BUFSIZ];
	char *cwd;

	prompt_line();

	while(fgets(input_str,100,stdin))
	{
		if(strcmp(input_str,"quit\n")==0)
		{
			printf("Bye~\n");
			return 0;
		}

		if(strcmp(input_str,"\n")==0)
		{
			prompt_line();
			continue;
		}

		input_str_tok = strtok_r(input_str, DELIM_CHAR, &save_ptr);
                options[0] = input_str_tok;


                for(int i = 1; i<10; i++)  // 옵션 받은 숫자만큼 토큰 분할
                {
                                options[i] = strtok_r(NULL, DELIM_CHAR, &save_ptr);
                                if(options[i] == NULL)
                                {
                                        options[i] = NULL;
                                        break;
                                }
                }

		if (strcmp(options[0],"cd")==0)
		{
			chdir(options[1]);
			prompt_line();
			continue;
		}


		pid = fork();


		if(pid == -1)
		{
			perror("fork error");
			exit(0);
		}

		else if(pid == 0)
		{
			getPATH = strtok_r(getPATH, ":", &save_ptr2);
			getPATH_tok[0] = getPATH;

			for(int i=1;i<10;i++)
                        {
                                getPATH_tok[i] = strtok_r(NULL, ":", &save_ptr2);

                                if(i==9)
                                {
                                        getPATH_tok[9] = "./";
                                }

                        }
			for(int i =0; i<10 ;i++)
			{
				strcpy(PATH_tok, getPATH_tok[i]);
				strcat(PATH_tok, "/");
				strcat(PATH_tok, options[0]);
				execve(PATH_tok, options, environ);
			}
			printf("Command '%s' is not found\n",options[0]);
			exit(1);

		}

		else
		{
			wait(&status);
		}

		prompt_line();
	}

	free(getPATH_tok);
	free(PATH_tok);
	return 0;
}
