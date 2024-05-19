#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int arr1[] = { 0 };
	int arr2[] = { 0 };
	int arr3[] = { 0 };
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	scanf("%d %d", &n, &m);
	printf("%d %d", m, n);
	for (i = 0; i < n; i++)
		scanf("%d", &arr1[i]);
	/*for (i = 0; i < m; i++)
		scanf("%d", &arr2[i]);
	for (i = 0; i < n; i++)
		printf("%d", arr1[i]);
	for (i = 0; i < m; i++)
		printf("%d", arr2[i]);*/
	return 0;
}