#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int i = 0;
int j = 0;
int arr1[3][5] = {
1,2,3,4,5,
6,7,8,9,10,
11,12,13,14,15
};
int arr2[3][5] = { {1,3},{8,9},{14} };
int arr3[3][5] = { 0 };
int main()
{
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 4; j++)
			printf("arr1[%d][%d] = %d\n", i, j, arr1[i][j]);
	}
	printf("arr1[0] = %d\n", arr1[0]);
	printf("***********\n");
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 4; j++)
			printf("arr1[%d][%d] = %p\n", i, j, &arr1[i][j]);
	}
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 4; j++)
			printf("arr2[%d][%d] = %d\n", i, j, arr2[i][j]);
	}
	/*for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 4; j++)
			scanf("%d", &arr3[i][j]);
	}
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 4; j++)
			printf("arr3[%d][%d] = %d\n", i, j, arr3[i][j]);
	}*/
	return 0;
}
