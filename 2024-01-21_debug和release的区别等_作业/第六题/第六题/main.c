#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
void print(int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		k = i;
		if (k <= (n - 1) / 2)
			k = k;
		else
			k = (n - 1) - k;
		for (j = 0; j < n; j++)
		{
			if (j<(n - 1) / 2 - k || j>(n - 1) / 2 + k)
				printf("  ");
			else
				printf("* ");
		}
		printf("\n");
	}
}
int main()
{
	int n;
	scanf_s("%d", &n);
	print(n);
	return 0;
}