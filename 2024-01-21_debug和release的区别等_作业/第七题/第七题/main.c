#define _CRT_SECURE_NO_WARNINGS 
//���0��100000֮������С�ˮ�ɻ������������
//��ˮ�ɻ�������ָһ��nλ�������λ���ֵ�n�η�֮��ȷ�õ��ڸ��������� : 153��1 ^ 3��5 ^ 3��3 ^ 3����153��һ����ˮ�ɻ�������
#include<stdio.h>
#include<math.h>
double calculate(int m, int n)
{
	if (m > 9)
		return pow(m % 10, n) + calculate(m / 10, n);
	else
		return pow(m, n);
}
int main()
{
	int i, j, k, ret;
	k = 1;

	for (i = 0; i < 100000; i++)
	{
		j = i;
		while (j > 9)
		{

			j = j / 10;
			k++;
		}
		if (i == calculate(i, k))
			printf("%d ", i);
		k = 1;
	}
	return 0;
}