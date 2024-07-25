#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void Func1()
{
	int a = 0;
	printf("%p\n", &a);
}

void Func2()
{
	int b = 1;
	printf("%p\n", &b);
}

int main()
{
	Func1();
	Func2();
	return 0;
}