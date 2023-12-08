#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{

	int i = 0;
	int j = 1;
	float k = 0.0;
	float a = 1.0;
	for (i = 0; i < 99; i++)
	{
		k += 1 / a * j;
		a++;
		j = -j;
	}
	printf("%f", k);
	return 0;
}