#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int num = 0;
	int x = 0;
	scanf("%d", &num);
	x = num % 3;
	if (0 == x)
		printf("这个数可以被3整除");
	if (1 == x)
		printf("这个数被三除后的余数是1");
	if (2 == x)
		printf("这个数被三除后的余数是2");
	return 0;
}