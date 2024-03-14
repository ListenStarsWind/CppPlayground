//"*"号打印，这个主要是找规律：
//比方说我们输入一个数字5，那就可以认为创建了一个5*5的棋盘，编号是01234然后我们看到这个“*”号
//实际是在对角线上显示的，如果把i看做行数，j看做列数就可以认为，“*”号会在i==j以及i+j==4上出现：
//题目链接：https://www.nowcoder.com/share/jump/9209693051710402272732
#define _CRT_SECURE_NO_WARNINGS
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
				if (i == j)
				{
					printf("*");
				}
				else if (i + j == import - 1)
				{
					printf("*");
				}
				else
					printf(" ");
			}
			printf("\n");
		}
	}

	return 0;
}