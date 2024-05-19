#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int i = 0;
int j = 0;
int k = 0;
int min = 0;
int max = 0;
int main()
{
	printf("请输入初始数据：\n");
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
		printf("这两个数的最大公约数是%d", min);
	}
	else
	{
		printf("这两个数的最大公约数是%d", i);
	}
	return 0;
}