#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 999;
	int j = 0;
	while (j < 1002)
	{
		if ((0 == i % 4 && 0 != i % 100) || 0 == i % 400)
			printf("%d ", i);
		i++;
		j++;
	}
	return 0;
}
//��ӡ1000�굽2000��֮�������