#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	printf("请输入两个数\n");
	scanf("%d%d", &i, &j);
	int k = 0;
	int a = 0;
	int min = (i > j) ? j : i;
	for (a = 1; a <= min; a++)
	{
		if (0 == i % a && 0 == j % a)
			k = a;
	}
	printf("这两个数的最大公约数是%d", k);
	return 0;
}