
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int i = 0;
int flag1 = 0;
int number = 0;
int conjecture = 0;

void cnumber()
{
	printf("��������µ����֣�\n");
	scanf("%d", &conjecture);
}

void RNG()
{
	srand((unsigned int)time(NULL));
	number = rand() % 100 + 1;
}


void menu()
{
	printf("************************************\n");
	printf("ѡ��1��������Ϸ\n");
	printf("ѡ��0���˳���Ϸ\n");
	printf("��������ѡ�������,1����0.\n");
	printf("************************************\n");
	scanf("%d", &flag1);
}

void InitialInterface()
{
	printf("��Ϸ��ʼ�����ڼ����У����Ժ�\n");
	printf("************************************\n");
	printf("************************************\n");
	printf("************************************\n");
	printf("����һ��С��Ϸ�������һ����ΧΪ1-100���������������Ҫ�³��������\n");

}

void game()
{
	int flag2 = 1;
	for (i = 1; i <= 5; i++)
	{

		if (conjecture < number)
		{
			printf("���С��\n");
			cnumber();
			continue;
		}
		else if (conjecture > number)
		{
			printf("��´���\n");
			cnumber();
			continue;
		}
		else
		{
			printf("��¶���\n");
			flag2 = 0;
			break;
		}
	}
	if (flag2)
		printf("��ѽ����������治��ѽ��Ҫ����һ����");
}



int main()
{
	InitialInterface();

	while (1)
	{
		menu();
		switch (flag1)
		{
		case 1:
		{
			RNG();
			cnumber();
			game();
		}
		break;
		case 0:
			goto finish;
			break;
		default:
			printf("ֻ��1��2ѽ��������ˣ�����������.\n");
			break;

		}
	}
finish:
	printf("��Ϸ��������ӭ�´����档\n");
	return 0;
}