#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  4月14日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：写一个函数打印一维整型数组arr的内容，不使用数组下标，使用指针。
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>

 //数组初始化函数
int initializer(int* const p_import, int sz)//使用const修饰指针，防止其指向遭到非法篡改
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;//指针预复位
	int push = 0;
	int pop = 0;
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		pop = scanf("%d", p + i);
		if (pop == EOF)
		{
			push = pop;
			break;
		}
		else
		{
			push += pop;
		}
	}
	return push;
}

//数组打印函数
int print(int* const p_import, int sz)//使用const修饰指针，防止其指向遭到非法篡改
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;//指针预复位
	int push = 0;
	int pop = 0;
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		pop = printf("%d ", *(p + i));
		if (pop == EOF)
		{
			push = pop;
			break;
		}
		else
		{
			push += pop;
		}
	}
	return push;
}

//主函数
int main()
{
	int arr[10] = { 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	printf_s("请输入%d个元素：\n", sz);
	while (EOF != initializer(arr, sz))
	{
		print(arr, sz);
		printf_s("\n");
	}
	return 0;
}
