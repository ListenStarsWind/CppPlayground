#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int arr1[10] = { 0 };
	int arr2[10] = { 0 };
	int arr3[10] = { 0 };
	for (i = 0; i < 10; i++)
		scanf("%d", &arr1[i]);
	for (i = 0; i < 10; i++)
		scanf("%d", &arr2[i]);
	for (i = 0; i < 10; i++)
		arr3[i] = arr1[i];
	for (i = 0; i < 10; i++)
		arr1[i] = arr2[i];
	for (i = 0; i < 10; i++)
		arr2[i] = arr3[i];
	for (i = 0; i < 10; i++)
		printf("%d ", arr1[i]);
	printf("\n");
	for (i = 0; i < 10; i++)
		printf("%d ", arr2[i]);
	return 0;
}
