#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
int j = 0;
int s = 0;
void game()
{
	while (1)
	{
		printf("���������µ���ֵ\n");
		scanf("%d", &j);
		if (j < s)
			printf("��С��\n");

		if (j > s)
			printf("�´���\n");

		if (j == s)
		{
			printf("��ϲ���¶��ˣ����������%d��\n", s);
			break;
		}
	}
}
int main()
{
	int i = 0;
	srand((unsigned int)time(NULL));
	s = rand() % 100 + 1;
	do
	{
		printf("**********************\n");
		printf("***��Ϸ׼����***\n");
		printf("***1.������Ϸ***\n");
		printf("***0.�˳���Ϸ***\n");
		printf("**********************\n");
		printf("***��ѡ��***\n");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			game();
			break;

		case 0:
			printf("�����˳���Ϸ");
			break;

		default:
			printf("�����������������\n");
			break;
		}
	} while (i);





}