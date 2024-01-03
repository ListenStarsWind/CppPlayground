#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int m = 0;
	int n = 0;
	int i = 0;
	int j = 0;
	scanf("%d %d", &m, &n);
	int arr[10][10] = { 0 };
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	}
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	return 0;
}