#include <stdlib.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
		int i = 0;
		char *stop = "quit";
		bool Go, Shell_go = true;	//������ ���� �ȵ����� ���� �Ҹ��Ȱ�.
		int state;
		char str[80];
		print("Shell ���α׷��� ���Ḧ ���� �ÿ�, '����'�� �Է����ּ���. \n");
		pid_t pid;

		while (Shell_go) {
				char FilenName[100];	//����� �Է� ���� �̸� ���� ����
				scanf("%s", FilenName);
				printf("Filie name : %s�� �˻��մϴ�", FilenName);

				char *Value;
				Value = getenv(FilenName[1]);

				if (Value != NULL)
				{
					printf("�ش� ���� ( %s)�� ã�ҽ��ϴ�.\n �ش� ���� ȯ�溯�� : %s", FilenName, Value);
				}


					//1. fork�߽����� �纻 ����. (�θ� fork ȣ�� - �ڽ� process ID ��ȯ, �ڽ� fork ȣ�� - 0 ��ȯ

				pid = fork();//fork ����

				if (pid < 0) {		//0���� ���� ��� ���� (-1)
					printf("PID ���� �߻�.\n");
					return -1;

				}
				else if (pid == 0) {			//�ڽ� ���μ���
					printf("child %d. id : %d\n", i, (long)getpid());
					exit(0);
				}
				else {				//�θ� ���μ���
					printf("parent  id : %d\n", (long)getpid());
					wait(0);
				}
			

	
				printf("���Ḧ ���� �ÿ���, 'quit'���ڿ��� �Է����ּ���.\n");
				scanf("%s", str);

				if (strcmp(str, stop) == 0) {
					printf("���α׷��� �����մϴ�.\n");
					Shell_go = false;

				}
				else {
					print("����ؼ� ���α׷��� �����մϴ�.\n");
					i++;
				}

		}

	return 0;
}
