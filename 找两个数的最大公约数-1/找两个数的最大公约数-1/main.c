#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	printf("������������\n");
	scanf("%d%d", &i, &j);
	int k = 0;
	int a = 0;
	int min = (i > j) ? j : i;
	for (a = 1; a <= min; a++)
	{
		if (0 == i % a && 0 == j % a)
			k = a;
	}
	printf("�������������Լ����%d", k);
	return 0;
}