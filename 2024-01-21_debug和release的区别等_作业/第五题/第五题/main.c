#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.1
 * 【完成日期】：	2024年  4月8日
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.0
 * 【历史日期】：	2024年 3月31日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，给20元，可以喝多少汽水（编程实现）。
 *******************************************************************************************/
#include<stdio.h>
#if 0
V1.0
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
#endif
int soda_logic(int money)
{
	if (money > 0)
	{
		int bottle = money;//初始空瓶数
		int drink = money;//初始喝的数
		while (bottle > 1)
		{
			drink = drink + bottle / 2;
			bottle = bottle / 2 + bottle % 2;
		}
		return drink;
	}
	else
	{
		return EOF;
	}
}
//使用公式，喝的总数等于钱 * 2 - 1
int soda_formula(int money)
{
	if (money > 0)
	{
		return money * 2 - 1;
	}
	else
	{
		return EOF;
	}
}

int main()
{
	int money = 0;
	while (scanf("%d", &money) != EOF)
	{
		if (soda_logic(money) != EOF)
		{
			printf("总共能喝到的汽水数目是%d。\n", soda_logic(money));
		}
		else
		{
			printf("喝个屁\n");
		}
	}
	return 0;
}