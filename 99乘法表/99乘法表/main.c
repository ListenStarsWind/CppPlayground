#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 1;
	int j = 0;
	int k = 0;
	while (i <= 9)
	{
		for (j = i; j <= 9; j++)
		{
			k = i * j;
			printf("%dx%d=%d ", i, j, k);
			if (9 == j)
				printf("\n");
		}
		i++;
	}
	return 0;
}