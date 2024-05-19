#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  5月7日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：strlen的模拟实现
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>
#include<string.h>
 //会写三种方法：前两种会创建新变量

 //第一种方法：计数器
size_t my_strlen_1(const char* cource)
{
	assert(cource);
	int count = 0;
	while (*cource)
	{
		count++;
		cource++;
	}
	return (size_t)count;
}

//第二种方法：指针-指针
size_t my_strlen_2(const char* const cource)
{
	assert(cource);
	char* destination = cource;
	while (*destination)
	{
		destination++;
	}
	return (size_t)(destination - cource);
}

//第三种方法：递归
size_t my_strlen_3(const char* cource)
{
	if (*cource)
	{
		return 1 + my_strlen_3(++cource);
	}
	else
	{
		return 0;
	}
}

int main()
{
	char str[] = { "hello word" };
	printf("标准库：%zd\n", strlen(str));
	printf("%d:%zd\n", 1, my_strlen_1(str));
	printf("%d:%zd\n", 2, my_strlen_2(str));
	printf("%d:%zd\n", 3, my_strlen_3(str));
	return 0;
}