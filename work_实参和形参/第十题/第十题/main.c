#include<stdio.h>
int init(int arr[], int sz)
{

	int i;
	for (i = 0; i < sz; i++)
		arr[i] = 0;
	return 0;
}

void print(int arr[], int sz)
{

	int i;
	for (i = 0; i < sz; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return;
}

void reverse(int arr[], int sz)
{

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
	int arr0[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
	int sz0 = sizeof(arr0) / sizeof(arr0[0]);
	int sz1 = sizeof(arr1) / sizeof(arr1[0]);
	print(arr1, sz1);
	init(arr1, sz1);
	print(arr1, sz1);
	reverse(arr0, sz0);
	print(arr0, sz0);
	return 0;
}