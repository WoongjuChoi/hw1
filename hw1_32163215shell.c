#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

struct cmd {
    char **argv;
    long argc;      /* argv의 사용자 길이 */
    long capa;      /* argv의 할당 된 길이 */
};

static void invoke_cmd(struct cmd *cmd);
static struct cmd* read_cmd(void);
static struct cmd* parse_cmd(char *cmdline);
static void free_cmd(struct cmd *p);
static void* xmalloc(size_t sz);
static void* xrealloc(void *ptr, size_t sz);

static char *program_name;

#define MAX_PATH	100
#define LF			10

int print_prompt()
{
	char *buffer = (char *)malloc(MAX_PATH); //char 버퍼를 주고
	char *value = (char *)getcwd (buffer, MAX_PATH); // char 버퍼의 크기를 주면

	if (value != 0)	fprintf(stdout,"SiSH:%s>",buffer);
	free (buffer); 
	
	return 0; //현재 작업 디렉토리가 반환된다.
}
int main(int argc, char *argv[]) //쉘의 개수와 쉘 문자열을 배열로 받음
{
    program_name = argv[0];
    for (;;) {
        struct cmd *cmd;
	print_prompt(); //프롬프트를 출력
	

        fflush(stdout); 
        cmd = read_cmd();
        if (cmd->argc > 0) {
            invoke_cmd(cmd);
        }
        free_cmd(cmd);
    }
    exit(0);
}

static void
invoke_cmd(struct cmd *cmd) // 커맨드를 호출하는 정적함수
{
    pid_t pid; // 프로세스 ID로 변수 pid를 선언
    
    pid = fork(); //fork 함수 실행
    if (pid < 0) { // 즉 -1을 반환
        perror("fork");
        exit(1);
    }
    if (pid > 0) {  /* 부모  */
        waitpid(pid, NULL, 0); // 자식 프로세스가 종료될때까지 기다린다.
    }
    else {          /* 자식 */
        execvp(cmd->argv[0], cmd->argv);
        /* 에러  */
        fprintf(stderr, "%s: command not found: %s\n", // 에러메세지를 출력
                        program_name, cmd->argv[0]);
        exit(1);
    }
}

#define LINE_BUF_SIZE 2048

static struct cmd *
read_cmd(void)
{
    static char buf[LINE_BUF_SIZE];
    char s1[10]; 
    char *s2="quit"; // quit이라는 문자열을 입력받는 배열
    if (fgets(buf, LINE_BUF_SIZE, stdin) == NULL) {
        printf("do you wanna quit the hw1_32163215shell  process?press the 'quit'\n"); // NULL로 초기화를 해주면 종료할거냐는 문구가 출력된다.
	scanf("%s",s1); 
	if(strcmp(s1,s2)==0)
	   exit(0);    //quit을 입력해주면 종료된다.
   }
    return parse_cmd(buf);
}

#define INIT_CAPA 16

static struct cmd*
parse_cmd(char *cmdline)
{
    char *p = cmdline; // p는프로세스를 가동하는 명령을 가진 파일이다. 
    struct cmd *cmd;

    cmd = xmalloc(sizeof(struct cmd)); //cmd는 구조체 크기만큼의 메모리를 할당한다
    cmd->argc = 0;
    cmd->argv = xmalloc(sizeof(char*) * INIT_CAPA);
    cmd->capa = INIT_CAPA;
    while (*p) {
        while (*p && isspace((int)*p)) { // *p와 isspace(공백문자이면 참)가 둘다 참일경우
            *p++ = '\0';
        }
        if (*p) {
            if (cmd->capa <= cmd->argc + 1) { 
                cmd->capa *= 2;
                cmd->argv = xrealloc(cmd->argv, cmd->capa);
            }
            cmd->argv[cmd->argc] = p;
            cmd->argc++;
        }
        while (*p && !isspace((int)*p)) {
            p++;
        }
    }
    cmd->argv[cmd->argc] = NULL; // cmd가 argv로 접근할 때 NULL값이면
    return cmd; // 명령어를 리턴한다.
}

static void
free_cmd(struct cmd *cmd)
{
    free(cmd->argv);
    free(cmd);
}

static void*
xmalloc(size_t size)
{
    void *p;

    p = malloc(size);
    if (!p) {
        perror("malloc");
        exit(1);
    }
    return p;
}

static void*
xrealloc(void *ptr, size_t size)
{
    void *p;

    if (!ptr) return xmalloc(size);
    p = realloc(ptr, size);
    if (!p) {
        perror("realloc");
        exit(1);
    }
    return p;
}
