#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"search.h"
int main()
{
	int couput;
	int j;
	printf("�������������ҵĺ�����\n");
	scanf("%d", couput);
	j = search(couput);
	if (1 == j)
		printf("�Ҳ����������������\n");

	return 0;
}