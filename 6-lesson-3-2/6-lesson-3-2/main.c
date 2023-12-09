#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 1;
	while (i <= 10)
	{
		i++;
		if (5 == i)
			continue;
		printf("%d ", i);

	}
	return 0;
}
//2 3 4 6 7 8 9 10 11