#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//int a = 0;
//int b = 0;
//int c = 0;
//int d = 0;
//int m = 0;
//int n = 0;
//int main()
//{
//	while (scanf("%d", &a) != EOF)
//	{
//		b = a;
//		c = a;
//		if (0 != a % 2)
//		{
//			for (m = 0; m <= b / 2; m++,b-=2)
//			{
//				for (n = b; n > 0; n--)
//				{
//					if (n == b || n == 1)
//						printf("*");
//					else
//						printf(" ");
//				}
//				printf("\n");
//			}
//			for (m = c / 2 + 1, d = 3; m < c; m++, d += 2)
//			{
//				for (n = d; n > 0; n--)
//				{
//					if (n == d || n == 1)
//						printf("*");
//					else
//						printf(" ");
//				}
//				printf("\n");
//			}
//		}
//		else
//		{
//			for (m = 0; m < b / 2; m++,b-=2)
//			{
//				for (n = b; n > 0; n--)
//				{
//					if (n == b || n == 1)
//						printf("*");
//					else
//						printf(" ");
//				}
//				printf("\n");
//
//			}
//			for (m = c / 2 + 1, d = 2; m < c; m++, d += 2)
//			{
//				for (n = d; n > 0; n--)
//				{
//					if (n == d || n == 1)
//						printf("*");
//					else
//						printf(" ");
//				}
//				printf("\n");
//			}
//		}
//		
//	}
//	return 0;
//}
#include<stdio.h>
int a = 0;

int m = 0;
int n = 0;

int main()
{
	while (scanf("%d", &a) != EOF)
	{
		for (m = 1; m <= a; m++)
		{

			for (n = 1; n <= a; n++)
			{
				if (n == m || n == a - m + 1)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");

		}
	}
	return 0;
}