#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int i = 0;
int j = 0;
int k = 0;
int min = 0;
int max = 0;
int main()
{
	printf("�������ʼ���ݣ�\n");
	scanf("%d%d", &i, &j);
	if (i != j)
	{
		min = (i > j) ? j : i;
		max = (i > j) ? i : j;
		while (j = max % min)
		{
			max = min;
			min = j;
		}
		printf("�������������Լ����%d", min);
	}
	else
	{
		printf("�������������Լ����%d", i);
	}
	return 0;
}