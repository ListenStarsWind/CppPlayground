#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	printf("请输入三个数\n");
	while (scanf("%d %d %d", &a, &b, &c) != EOF)
	{
		if (a < b)
		{
			i = a;
			a = b;
			b = i;
		}
		if (a < c)
		{
			j = a;
			a = c;
			c = j;
		}
		if (b < c)
		{
			k = b;
			b = c;
			c = k;
		}
		printf("%d %d %d\n", a, b, c);
	}
	return 0;
}




