#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int arr[10] = { 0 };
	printf("���������ݸ���");
	scanf("%d", &i);
	for (j = 0; j < i; j++)
		scanf("%d", &arr[j]);
	for (j = 0; j < i; j++)
	{
		if (k < arr[j])
			k = arr[j];
	}
	printf("��������%d", k);
	return 0;
}