#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int left = 0;
	int right = 0;
	int flag = 1;
	printf("������Ҫ�ҵ���\n");
	scanf("%d", &i);
	j = sizeof(arr) / sizeof(arr[0]);
	right = j - 1;
	while (left <= right)
	{
		k = (left + right) / 2;
		if (i < arr[k])
			right = k - 1;
		if (i > arr[k])
			left = k + 1;
		if (i == arr[k])
		{
			flag = 0;
			printf("�ҵ��ˣ����������%d\n", i);
			break;
		}
	}
	if (flag)
		printf("�Ҳ��������������");
	return 0;
}