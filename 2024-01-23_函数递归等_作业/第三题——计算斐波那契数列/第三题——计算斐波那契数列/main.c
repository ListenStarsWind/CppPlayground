#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
int rabbit_recursion(int n)//쳲����������ֳ���������
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 1;
	else
		return rabbit_recursion(n - 1) + rabbit_recursion(n - 2);
}

int rabbit_iteration(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 1;
	else
	{
		int i;
		int a = 1;
		int b = 1;
		int c;
		for (i = 3; i <= n; i++)
		{
			c = a + b;
			a = b;
			b = c;
		}
		return c;
	}
}
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		printf("��n=%dʱ��\n", n);
		printf("�ݹ�Ľ����%d\n", rabbit_recursion(n));
		printf("�����Ľ����%d\n", rabbit_iteration(n));
	}
	return 0;
}