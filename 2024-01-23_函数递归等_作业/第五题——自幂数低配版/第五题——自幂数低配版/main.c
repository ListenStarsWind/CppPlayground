#define _CRT_SECURE_NO_WARNINGS 
//дһ���ݹ麯��DigitSum(n)������һ���Ǹ����������������������֮��
//���磬����DigitSum(1729)����Ӧ�÷���1 + 7 + 2 + 9�����ĺ���19
//���룺1729�������19
#include<stdio.h>
int DigitSum(int n)
{
	if (n > 9)
		return n % 10 + DigitSum(n / 10);
	else
		return n;
}
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		printf("%d\n", DigitSum(n));
	}
	return 0;
}
