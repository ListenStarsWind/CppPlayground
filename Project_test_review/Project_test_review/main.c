#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int num = 0;
	int x = 0;
	scanf("%d", &num);
	x = num % 3;
	if (0 == x)
		printf("��������Ա�3����");
	if (1 == x)
		printf("��������������������1");
	if (2 == x)
		printf("��������������������2");
	return 0;
}