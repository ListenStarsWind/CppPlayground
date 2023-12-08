#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 1;
	int k = 0;
	for (i = 0; i < 99; i++)
	{
		if (9 == j % 10)
		{
			k++;
		}
		if (9 == j / 10)
		{
			k++;
		}
		j++;
	}
	printf("%d\n", k);
	printf("%d", j);
}