#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 9;
	int k = 1;
	while (i < 99)
	{
		k++;
		i += 10;
	}
	printf("%d\n", k);
	return 0;
}