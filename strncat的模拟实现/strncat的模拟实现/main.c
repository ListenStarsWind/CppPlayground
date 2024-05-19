#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  5月19日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：strncat的模拟实现
 *******************************************************************************************/

#include<stdio.h>
#include<assert.h>
#include<string.h>

char* my_strncat(char* destination, const char* source, size_t num)
{
	assert(destination && source);
	char* ret = destination;
	while (*destination)
	{
		destination++;
	}
	size_t len = strlen(source);
	if (len > num)
	{
		while (num--)
		{
			*destination++ = *source++;
		}
		*destination = 0;
	}
	else
	{
		while (*destination++ = *source++)
		{
			;
		}
	}

	return ret;
}

int main()
{
	char arr[100] = "xxxxxxxxxxx\0xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	char* str = "Hope Is the Thing With Feathers";
	size_t n = strlen(str);
	my_strncat(arr, str, n + 2);
	printf("%s\n", arr);
	return 0;
}