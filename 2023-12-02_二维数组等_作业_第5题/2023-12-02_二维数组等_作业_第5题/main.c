#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	double a = 0;
	int b = 0;
	int arr[10] = { 0 };
	i = sizeof(arr) / sizeof(arr[0]);
	b = i;
	i -= 1;
	printf("�������ʼ����\n");
	for (j = 0; j <= i; j++)
		scanf("%d", &arr[j]);
	for (j = 0; j <= i; j++)
		k += arr[j];
	a = k * 1.0 / b;
	printf("���ǵ�ƽ������%lf\n", a);
	return 0;
}