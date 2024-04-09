#define _CRT_SECURE_NO_WARNINGS 
//求Sn = a + aa + aaa + aaaa + aaaaa的前5项之和，其中a是一个数字，
//
//例如：2 + 22 + 222 + 2222 + 22222
//
#include<math.h>
#include<stdio.h>

int calculate(int m)
{
	int ret = 0;
	int j;
	int k = m;
	for (j = 1; j <= 5; j++)
	{
		ret += m;
		m += pow(10, j) * k;
	}
	return ret;

}
int main()
{
	int n;
	scanf_s("%d", &n);
	printf("%d", calculate(n));
	return 0;
}
