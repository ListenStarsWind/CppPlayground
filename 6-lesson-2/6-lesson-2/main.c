#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	printf("请输入一个整数\n");
	scanf("%d", &i);
	do
	{
		i = i / 10;
		j++;
	} while (i);
	printf("这是一个%d位数\n", j);
	return 0;
}