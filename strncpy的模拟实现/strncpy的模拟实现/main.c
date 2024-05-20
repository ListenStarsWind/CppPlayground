#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  5月20日
 * 【更新内容】：代码效率优化
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  5月19日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：strncpy的模拟实现
 *******************************************************************************************/

#include<stdio.h>
#include<assert.h>
#include<string.h>

# if 0
char* my_strncpy(char* destination, const char* source, size_t num)
{
	assert(destination && source);
	char* ret = destination;
	size_t len = strlen(source);
	if (len < num)
	{
		while (*destination++ = *source++)
		{
			;
		}
		size_t i = 0;
		for (; i < num - len - 1; i++)
		{
			*destination++ = 0;
		}
	}
	else
	{
		while (num--)
		{
			*destination++ = *source++;
		}
	}
	return ret;
}
#endif

char* MyStrncpy(char* destination, const char* source, size_t num)
{
	assert(destination && source);
	char* ret = destination;
	size_t i = 0;
	for (; source[i] != '\0' && i < num; i++)
	{
		destination[i] = source[i];
	}
	if (num > i)
	{
		for (; i < num; i++)
		{
			destination[i] = 0;
		}
	}
	return ret;
}

int main()
{
	char arr[50] = "xxxxxxxxxxxxxxxxxxxxxxx";
	char* str = "hello word";
	size_t n = strlen(str);
	MyStrncpy(arr, str, n + 2);
	printf("%s\n", arr);
	return 0;
}