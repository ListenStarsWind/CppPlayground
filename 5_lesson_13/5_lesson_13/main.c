#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	while (i <= 100)
	{
		if (0 == i % 3)
			j = j + i;
		i++;
	}
	printf("%d\n", j);
	return 0;
}