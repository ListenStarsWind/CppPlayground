#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int a = 0;
int m = 0;
int n = 0;
int main()
{
	while (scanf("%d", &a) != EOF)
	{
		for (m = 1; m <= a; m++)
		{

			for (n = 1; n <= a; n++)
			{
				if (n == m || n == a - m + 1)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");

		}
	}
	return 0;
}