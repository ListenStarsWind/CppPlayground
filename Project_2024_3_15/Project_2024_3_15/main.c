#define _CRT_SECURE_NO_WARNINGS
//这是一个测试类型的项目，其目的是创建一个自定义的函数，该函数的功能是将两个整型变量相加求和，并返回与其结果。
#include<stdio.h>
int Add(int x, int y)
{
	return x + y;
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d", Add(a, b));
	return 0;
}