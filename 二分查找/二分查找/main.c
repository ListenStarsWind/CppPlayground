#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"search.h"
int main()
{
	int flag = 0;
	int couput;
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]);
	int mind = 0;
	printf("�������������ҵ����֣�\n");
	scanf("%d", &couput);

	while (left <= right)
	{
		mind = (left + right) / 2;
		if (couput < arr[mind])
			right = mind - 1;
		else if (couput > arr[mind])
			left = mind + 1;
		else
		{
			flag = 1;
			break;
		}
	}

	if (flag == 1)
		printf("�ҵ�������Ѱ�ҵ��������������е��±���%d��\n", mind);
	else
		printf("���������û��������Ҫ������\n");
	return 0;
}