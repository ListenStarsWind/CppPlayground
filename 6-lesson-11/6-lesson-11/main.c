#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//int main()
//{
//	int i = 0;
//	int arr[10] = { 0 };
//	printf("����������\n");
//	for (i = 0; i <= 9; i++)
//		scanf("%d", &arr[i]);
//	for (i = 0; i <= 9; i++)
//		printf("%d ", arr[i]);
//
//	return 0;
//}
int main()
{
	int i = 0;
	int j = 0;
	int arr[10] = { 0 };
	j = sizeof(arr) / sizeof(arr[0]);
	printf("����������\n");
	for (i = 0; i <= (j - 1); i++)
		scanf("%d", &arr[i]);
	for (i = 0; i <= (j - 1); i++)
		printf("%d ", arr[i]);
	printf("\n���������%d��Ԫ��\n", j);
	for (i = 0; i <= (j - 1); i++)
		printf("arr[%d]=%p\n", i, arr[i]);



	return 0;
}
