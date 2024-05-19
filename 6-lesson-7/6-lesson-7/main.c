#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 100; i <= 200; i++)
	{
		for (j = 2; j <= (i - 1); j++)
		{
			if (0 == i % j)
				goto next;
		}
		printf("%d ", i);
		k++;
	next:
		;
	}
	printf("\n%d\n", k);
	return 0;
}
//找到100~200之间的素数（素数又称质数，是只能被1
//int main()
//{
//	int i = 0;
//	int j = 0;
//	int a = 0;
//	for (i = 100; i <= 200; i++)
//	{
//		int k = 0;
//		for (j = 2; j <= (i - 1); j++)
//		{
//			if (0 == i % j)
//			{
//				k = 1;
//				break;
//			}
//		}
//		if (0 == k)
//		{
//			a++;
//			printf("%d ", i);
//		}
//	}
//	printf("\n%d\n", a);
//	return 0;
//}