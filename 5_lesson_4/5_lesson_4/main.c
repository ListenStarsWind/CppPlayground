#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0;
	printf("����������");
	scanf("%d", &a);
	switch (a % 3)
	{
	case 0:
		printf("��������Ա�������\n");

	case 1:
		printf("������һ\n");

	case 2:
		printf("�����Ƕ�\n");

	}
	return 0;
}