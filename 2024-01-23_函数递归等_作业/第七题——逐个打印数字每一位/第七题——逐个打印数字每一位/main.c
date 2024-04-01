#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void print(int n)
{
	if (n > 9)
	{
		print(n / 10);
		printf("%d ", n % 10);
	}
	else
		printf("%d ", n);
}

int main()
{
	print(12345);
	return 0;
}
