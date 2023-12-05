#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	unsigned long long int i = 0;
	unsigned long long int j = 0;
	scanf("%d", &i);
	while (i)
	{
		j = i % 10;
		printf("%d", j);
		i = i / 10;
	}
	return 0;
}