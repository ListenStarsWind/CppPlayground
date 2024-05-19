#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  5月14日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：memmove的模拟实现
 *******************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<assert.h>

 //第一版：sour < dest < (char*)sour + num
void* my_memmove_1(void* destination, const void* source, size_t num)
{
	assert(destination && source);
	void* ret = destination;
	if (source < destination && destination < (char*)source + num)
	{
		while (num--)
		{
			*((char*)destination + num) = *((char*)source + num);
		}
	}
	else
	{
		while (num--)
		{
			*((char*)destination) = *((char*)source);
			(char*)destination = (char*)destination + 1;
			(char*)source = (char*)source + 1;
		}
	}
	return ret;
}

//第二版：sour < (char*)dest + num < (char*)sour + num
void* my_memmove_2(void* destination, const void* source, size_t num)
{
	assert(destination && source);
	void* ret = destination;
	if (source < (char*)destination + num && (char*)destination + num < (char*)source + num)
	{
		while (num--)
		{
			*((char*)destination) = *((char*)source);
			(char*)destination = (char*)destination + 1;
			(char*)source = (char*)source + 1;
		}

	}
	else
	{
		while (num--)
		{
			*((char*)destination + num) = *((char*)source + num);
		}
	}
	return ret;
}

int main()
{
	int i = 0;
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int arr2[10] = { 0 };

	//memmove(arr1 + 2, arr1, 5 * sizeof(int)):      1 2 1 2 3 4 5 8 9 10    
	//memmove(arr1, arr1 + 2, 5 * sizeof(int)):      3 4 5 6 7 6 7 8 9 10
	my_memmove_2(arr1, arr1 + 2, 5 * sizeof(int));
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr1[i]);
	}
	return 0;
}