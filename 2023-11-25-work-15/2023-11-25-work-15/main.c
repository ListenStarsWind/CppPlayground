#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int arr[10] = { 1,2,3,4,5,6,7,23,567,123 };
	for (j = 0; j < 9; j++)
	{
		if (k < arr[j])
			k = arr[j];
	}
	printf("最大的数是%d", k);
	return 0;
}