#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0;
	scanf("%d", &a);
	switch (a)
	{
	default:
		printf("输入错误");
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		printf("是工作日");
		break;
	case 6:
	case 7:
		printf("是休息日");
		break;

	}
	return 0;
}