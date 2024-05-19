#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  月日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：优化LCD12864部分代码
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

typedef unsigned char uchar;
typedef unsigned char uchar;
typedef unsigned int uint;
void Text_scrolling_right(char arr[])
{
	int i = 0;
	int j = 0;
	size_t len = strlen(arr);
	for (i = 0; i < 2; i++)
	{
		char push = arr[len - 1];
		for (j = len - 2; j >= 0; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[0] = push;

	}

}

//文本滚动函数，会将输入字符串向前循环滚动两个字节长度
void Text_scrolling_left(char str[])
{
	size_t len = strlen(str);//放心使用strlen()不管是数组还是指针都可以使用，且包含空格，不包含‘\0’
	int i = 0;
	int j = 0;
	for (i = 0; i < 2; i++)
	{
		char push = str[0];
		for (j = 0; j < len - 1; j++)
		{
			str[j] = str[j + 1];
		}
		str[len - 1] = push;
	}
}


void test1()
{
	static char arr1[30] = { "智能家具模拟控制" };
	static char arr2[30] = { "AHZYJSXY1      " };
	size_t sz1 = 0;
	size_t sz2 = 0;
	sz1 = sizeof(arr1) / sizeof(arr1[0]);
	sz2 = sizeof(arr2) / sizeof(arr2[0]);
	printf("%s\n", arr1);
	printf("%s\n", arr2);
	Text_scrolling_left(arr1);
	Text_scrolling_left(arr2);

}


void test2()
{
	static char arr1[30] = { "智能家具模拟控制" };
	static char arr2[30] = { "AHZYJSXY1      " };
	size_t sz1 = 0;
	size_t sz2 = 0;
	sz1 = sizeof(arr1) / sizeof(arr1[0]);
	sz2 = sizeof(arr2) / sizeof(arr2[0]);
	printf("%s\n", arr1);
	printf("%s\n", arr2);
	Text_scrolling_right(arr1);
	Text_scrolling_right(arr2);
}

int main()
{
	test2();
	printf("\n");
	test2();
	printf("\n");
	test2();
	printf("\n");
	return 0;
}