//ʵ��һ����������ӡ�˷��ھ����ھ���������������Լ�ָ��
//�磺����9�����9 * 9�ھ������12�����12 * 12�ĳ˷��ھ���
#include<stdio.h>
void PrintFormula(int k)
{
	int i, j;
	for (i = 1; i <= k; i++)
	{
		for (j = 1; j <= i; j++)
			printf("%d*%d=%d ", j, i, i * j);
		printf("\n");
	}
}

int main()
{
	PrintFormula(12);
	return 0;
}