//实现一个函数，打印乘法口诀表，口诀表的行数和列数自己指定
//如：输入9，输出9 * 9口诀表，输出12，输出12 * 12的乘法口诀表。
#include<stdio.h>
void PrintFormula(int k)
{
	int i, j;
	for (i = 1; i <= k; i++)
	{
		for (j = 1; j <= i; j++)
			printf("%d*%d=%d ", j, i, i * j);
		printf("\n");
	}
}

int main()
{
	PrintFormula(12);
	return 0;
}