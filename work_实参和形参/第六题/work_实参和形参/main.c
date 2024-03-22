// arr 是查找的数组
//left 数组的左下标
//right 数组的右下标
//key 要查找的数字
//写一个二分查找函数
//功能：在一个升序数组中查找指定的数值，找到了就返回下标，找不到就返回 - 1.
#include<stdio.h>
int bin_search(int arr[], int left, int right, int key)
{
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (arr[middle] == key)
			return middle;
		else if (arr[middle] > key)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return -1;
}

int main()
{
	int arr[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	printf("%d", bin_search(arr, 0, 10, 11));
	return 0;
}