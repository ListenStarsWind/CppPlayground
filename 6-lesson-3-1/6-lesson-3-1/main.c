#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 1;
	while (i <= 10)
	{
		if (6 == i)
			break;
		printf("%d ", i);
		i++;
	}
	return 0;
}