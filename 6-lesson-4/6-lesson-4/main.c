#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//int main()
//{
//	int i = 0;
//	for (i = 1; i <= 10; i++)
//	{
//		if (5 == i)
//			break;
//		printf("%d ", i);
//	}
//	return 0;
//}
//1 2 3 4 
int main()
{
	int i = 0;
	for (i = 1; i <= 10; i++)
	{
		if (5 == i)
			continue;
		printf("%d ", i);
	}
	return 0;
}
//1 2 3 4 6 7 8 9 10 