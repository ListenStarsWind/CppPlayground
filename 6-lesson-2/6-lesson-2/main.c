#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	printf("������һ������\n");
	scanf("%d", &i);
	do
	{
		i = i / 10;
		j++;
	} while (i);
	printf("����һ��%dλ��\n", j);
	return 0;
}