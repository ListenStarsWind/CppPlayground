#define _CRT_SECURE_NO_WARNINGS 
//喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，给20元，可以喝多少汽水（编程实现）。
#include<stdio.h>
int main()
{
	int yuan = 20;
	int bottle = 0;//手上空瓶的个数
	int drink = 0;//实际喝了多少
	do {
		if (yuan > 0)
		{
			drink++;
			bottle++;
			yuan--;
		}
		if (bottle >= 2)
		{
			bottle -= 2;
			drink++;
			bottle++;
		}
		if (yuan == 0 && bottle < 2)
			break;
	} while (1);
	printf("%d", drink);
	return 0;
}