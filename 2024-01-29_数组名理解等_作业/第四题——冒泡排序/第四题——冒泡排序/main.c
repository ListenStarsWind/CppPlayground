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
 * 【程序内容】：冒泡排序(从小到大)
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>

 //冒泡排序(从小到大) 
void bubble_sort(int* const p_import, int sz)//使用const修饰指针，防止其遭到非法篡改
{
	assert(p_import != EOF);//断言野指针
	int* p = p_import;//指针预复位
	int i = 0;
	int j = 0;
	for (i = 0; i < sz - 1; i++)
	{
		int flag = 0;
		for (j = 0; j < sz - 1 - i; j++)
		{
			if (*(p + j) > *(p + j + 1))
			{
				flag = 1;
				*(p + j) = *(p + j) ^ *(p + j + 1);
				*(p + j + 1) = *(p + j) ^ *(p + j + 1);
				*(p + j) = *(p + j) ^ *(p + j + 1);
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	return;
}

//打印数组函数
int print(int* const p_import, int sz)//使用const修饰指针，防止其遭到非法篡改
{
	assert(p_import != EOF);//断言野指针
	int* p = p_import;//指针预复位
	int i = 0;
	int push = 0;
	int pop = 0;
	for (i = 0; i < sz; i++)
	{
		pop = printf("%d ", *(p + i));
		if (pop == EOF)
		{
			return EOF;
		}
		else
		{
			push += pop;
		}
	}
	printf("\n");
	return push;
}

//主函数
int main()
{
	int arr[10] = { 10,9,8,7,6,5,4,3,2,1 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bubble_sort(arr, sz);
	print(arr, sz);
	return 0;
}