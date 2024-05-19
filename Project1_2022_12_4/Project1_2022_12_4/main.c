#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0;
	printf("请输入数据");
	scanf("%d", &a);
	switch (a % 3)
	{
	case 0:
		printf("这个数可以被三整除");
		break;
	case 1:
		printf("余数是一");
		break;
	case 2:
		printf("余数是二");
		break;
	}
	return 0;
}