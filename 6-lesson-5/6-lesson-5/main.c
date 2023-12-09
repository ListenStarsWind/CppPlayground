#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//int main()
//{
//	int i = 1;
//	do
//	{
//		if (5 == i)
//			break;
//		printf("%d ", i);
//		i++;
//	} while (i <= 10);
//	return 0;
//}
//1 2 3 4 
int main()
{
	int i = 1;
	do
	{
		if (5 == i)
			continue;
		printf("%d ", i);
		i++;
	} while (i <= 10);
	return 0;
}
//1 2 3 4  