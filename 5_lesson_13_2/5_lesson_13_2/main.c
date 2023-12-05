#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 3;
	int j = 0;
	while (i <= 100)
	{
		j = j + i;
		i += 3;
	}
	printf("%d\n", j);
	return 0;

}