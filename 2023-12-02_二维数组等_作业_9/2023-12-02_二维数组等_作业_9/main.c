#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int a = 0;
int m = 0;
int n = 0;
int main()
{
	while (scanf("%d", &a) != EOF)
	{
		for (m = 0; m < a; m++)
		{
			if (m == 0 || m == a - 1)
			{
				for (n = 0; n < 2 * a - 1; n++)
				{
					if (0 == n % 2)
						printf("*");
					else
						printf(" ");
				}
				printf("\n");
			}
			else
			{
				for (n = 0; n < 2 * a - 1; n++)
				{
					if (0 == n || 2 * a - 2 == n)
						printf("*");
					else
						printf(" ");
				}
				printf("\n");
			}
		}
	}
	return 0;
}