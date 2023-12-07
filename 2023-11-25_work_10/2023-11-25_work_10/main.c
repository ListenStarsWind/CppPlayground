#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	printf("ÇëÊäÈëÊý¾Ý");
	scanf("%d %d %d", &i, &j, &k);
	if (i > j && i > k)
	{
		printf("%d ", i);
		if (j > k)
		{
			printf("%d ", j);
			printf("%d ", k);
		}
		else
		{
			printf("%d ", k);
			printf("%d ", j);
		}

	}
	if (j > i && j > k)
	{
		printf("%d ", j);
		if (i > k)
		{
			printf("%d ", i);
			printf("%d ", k);
		}
		else
		{
			printf("%d ", k);
			printf("%d ", i);
		}

	}
	if (k > i && k > j)
	{
		printf("%d ", k);
		if (i > j)
		{
			printf("%d ", i);
			printf("%d ", j);
		}
		else
		{
			printf("%d ", j);
			printf("%d ", i);
		}

	}

	return 0;
}
