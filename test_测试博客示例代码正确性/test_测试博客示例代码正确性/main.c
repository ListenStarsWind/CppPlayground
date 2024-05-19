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
 * 【程序内容】：
 *******************************************************************************************/
#include<stdio.h>
#include<string.h>
#include<assert.h>

void* my_memcpy(void* destination, const void* source, size_t num)
{
	assert(destination && source);
	void* ret = destination;
	while (num--)
	{
		*((char*)destination) = *((char*)source);
		(char*)destination = (char*)destination + 1;
		//还有种不推荐的写法：((char*)source)++;用括号强制改变操作符结合性
		(char*)source = (char*)source + 1;
	}
	return ret;
}

int main()
{
	int i = 0;
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int arr2[10] = { 0 };
	my_memcpy(arr1 + 2, arr1, 5 * sizeof(int));
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr1[i]);
	}
	return 0;
}
