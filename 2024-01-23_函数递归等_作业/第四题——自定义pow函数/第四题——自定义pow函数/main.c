#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int powi(int m, int k)//求m的k次方
{
	if (k == 1)
		return m;
	else
		return m * powi(m, k - 1);
}

int main()
{
	int m, k;
	while (EOF != scanf("%d%d", &m, &k))
		printf("%d的%d次方是%d。\n", m, k, powi(m, k));
	return 0;
}