// arr �ǲ��ҵ�����
//left ��������±�
//right ��������±�
//key Ҫ���ҵ�����
//дһ�����ֲ��Һ���
//���ܣ���һ�����������в���ָ������ֵ���ҵ��˾ͷ����±꣬�Ҳ����ͷ��� - 1.
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