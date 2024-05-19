#include<stdio.h>
int init(int arr[])
{
	int sz = sizeof(arr) / sizeof(arr[0]);
	int i;
	for (i = 0; i < sz; i++)
		arr[i] = 0;
	return 0;
}

void print(int arr[])
{
	int sz = sizeof(arr) / sizeof(arr[0]);
	int i;
	for (i = 0; i < sz; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return;
}

void reverse(int arr[])
{
	int sz = sizeof(arr) / sizeof(arr[0]);
	int i, left, right;
	for (left = 0, right = sz - 1; left <= right; left++, right--)
	{
		i = arr[left];
		arr[left] = arr[right];
		arr[right] = i;
	}
}
int main()
{
	int arr0[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("==%d\n==", sizeof(arr1) / sizeof(arr1[0]));
	print(arr1);
	init(arr1);
	print(arr1);
	reverse(arr0);
	print(arr0);
	return 0;
}