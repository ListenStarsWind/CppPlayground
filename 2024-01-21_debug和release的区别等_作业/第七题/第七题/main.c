#define _CRT_SECURE_NO_WARNINGS 
//求出0～100000之间的所有“水仙花数”并输出。
//“水仙花数”是指一个n位数，其各位数字的n次方之和确好等于该数本身，如 : 153＝1 ^ 3＋5 ^ 3＋3 ^ 3，则153是一个“水仙花数”。
#include<stdio.h>
#include<math.h>
double calculate(int m, int n)
{
	if (m > 9)
		return pow(m % 10, n) + calculate(m / 10, n);
	else
		return pow(m, n);
}
int main()
{
	int i, j, k, ret;
	k = 1;

	for (i = 0; i < 100000; i++)
	{
		j = i;
		while (j > 9)
		{

			j = j / 10;
			k++;
		}
		if (i == calculate(i, k))
			printf("%d ", i);
		k = 1;
	}
	return 0;
}