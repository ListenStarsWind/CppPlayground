#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"search.h"
int main()
{
	int couput;
	int j;
	printf("请输入您所查找的函数：\n");
	scanf("%d", couput);
	j = search(couput);
	if (1 == j)
		printf("找不到您所输入的数。\n");

	return 0;
}