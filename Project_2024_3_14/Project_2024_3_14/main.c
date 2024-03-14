#define _CRT_SECURE_NO_WARNINGS
//像这种图案打印题，一定要画画图，否则很难找的规律的，你可以看下同一天之前提交的代码注释联系一下；
//题目：https ://www.nowcoder.com/share/jump/9209693051710403447399
#include<stdio.h>
int main()
{
	int i, j, import;
	while (EOF != scanf("%d", & import))
	{
		for (i = 0; i < import; i++)
		{
			for (j = 0; j < import; j++)
			{
				if (i == 0 || i == import - 1)
					printf("* ");
				else if (j == 0 || j == import - 1)
					printf("* ");
				else
					printf("  ");
			}
			printf("\n");
		}
	}
	return 0;
}
