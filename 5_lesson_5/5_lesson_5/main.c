#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0;
	scanf("%d", &a);
	switch (a)
	{
	default:
		printf("�������");
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		printf("�ǹ�����");
		break;
	case 6:
	case 7:
		printf("����Ϣ��");
		break;

	}
	return 0;
}