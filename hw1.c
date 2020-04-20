#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//������Ʈ �Լ�
void type_prompt()
{ 
             static int firsttime =1;
             if(firstime) {
             printf("first time PATH : %d USER : %d ",getenv("USER"), getenv("PATH"));
             firsttime =0;
             }          
	printf("#");
}
//����� ��� �б�
void read_command(char cmd[], char* par[])
{
             //�Է� �� ��ɾ� ����
	char line[1024];
	int count = 0, i = 0, j = 0;
	char* array[100], * pch;
	for (;;)
	{
		int c = fgetc(stdin);
		line[count++] = (char)c;
		if (c == '\n')break;

	}
	if (count == 1)return;
	pch = strtok(line, "\n");
             //���� Ű(���๮��)�� ������ �ܾ�� ����
	while (pch !=NULL)
	{
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}
  
            strcpy(cmd,array[0]);
	for (int j = 0; j < i; j++)
		par[j] = array[j];
	par[i] = NULL; //�Ŀ� exe�� ���� parameter list�� null�� ����
}


int main(void)
{
	char cmd[1000], command[100], * parameters[20]; //��ɾ��� �����ϴ� �迭�� parameter�� ������ ������
	char* envp[] = { (char*)"PATH=/bin",0 }; //  ȯ�溯��, ����� bin�� �ֱ� ������ PATH=/bin 
	while (1) {
		type_prompt(); //������Ʈ ����
		read_command(command, parameters); // ����� �а��ϴ� �Լ�
		if (fork() != 0) //�ڽ� ���μ��� ����
			wait(NULL); // �θ� ���μ����� ���
		else
		{
			strcpy(cmd "/bin/"); //bin ���丮�� ������
			strcat(cmd, command); //����� ��� ������
			execve(cmd, parameters, envp); // ����� ����
		}
		if (strcmp(command, "exit") == 0)  //�������� ���� exit
			break;
	}
	return 0;
}
