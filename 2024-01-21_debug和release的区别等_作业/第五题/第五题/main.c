#define _CRT_SECURE_NO_WARNINGS 
//����ˮ��1ƿ��ˮ1Ԫ��2����ƿ���Ի�һƿ��ˮ����20Ԫ�����Ժȶ�����ˮ�����ʵ�֣���
#include<stdio.h>
int main()
{
	int yuan = 20;
	int bottle = 0;//���Ͽ�ƿ�ĸ���
	int drink = 0;//ʵ�ʺ��˶���
	do {
		if (yuan > 0)
		{
			drink++;
			bottle++;
			yuan--;
		}
		if (bottle >= 2)
		{
			bottle -= 2;
			drink++;
			bottle++;
		}
		if (yuan == 0 && bottle < 2)
			break;
	} while (1);
	printf("%d", drink);
	return 0;
}