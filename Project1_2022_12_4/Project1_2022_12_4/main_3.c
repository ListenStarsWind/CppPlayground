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
		printf("��������Ա�������");

	case 1:
		printf("������һ");

	case 2:
		printf("�����Ƕ�");

	}
	return 0;
}
