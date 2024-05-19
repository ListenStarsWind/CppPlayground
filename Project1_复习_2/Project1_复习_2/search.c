#define _CRT_SECURE_NO_WARNINGS
int search(int i)
{
	int flag = 1;
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]) - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (i < arr[middle])
		{
			right = middle - 1;
		}
		else if (i > arr[middle])
		{
			left = middle + 1;
		}
		else
		{
			flag = 0;
			printf("找到了这个数，它在数组中的下标是%d.\n", middle);
			break;
		}
	}
	return flag;
}