#define _CRT_SECURE_NO_WARNINGS 
//�ݹ�ͷǵݹ�ֱ�ʵ����n�Ľ׳ˣ���������������⣩
#include<stdio.h>
int factorial_recursion(int n)
{
	if (n > 1)
		return n * factorial_recursion(n - 1);
	else
		return n;
}
int factorial_iteration(int n)
{
	int m = 1;
	int i = 0;
	for (i = 1; i <= n; i++)
		m *= i;
	return m;
}
int main()
{
	int i = factorial_recursion(6);
	int j = factorial_iteration(6);
	printf("%d\n", i);
	printf("%d\n", j);
	return 0;
}
