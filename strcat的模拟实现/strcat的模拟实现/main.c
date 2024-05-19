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
 * 【程序内容】：strcat的模拟实现
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>
#include<string.h>

 //初代版
char* my_strcpy_0(char* destination, const char* source)
{
	assert(destination && source);
	char* ret = destination;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = *source;
	return ret;
}

//一代优化
char* my_strcpy_1(char* destination, const char* source)
{
	assert(destination && source);
	char* ret = destination;
	do
	{
		*destination++ = *source++;

	} while (*(source - 1));
	return ret;
}

//仿标准库型
char* my_strcpy(char* destination, const char* source)
{
	assert(destination && source);
	char* ret = destination;
	while (*destination++ = *source++)
	{
		;
	}

	return ret;
}

int main()
{
	char to[] = { "chnwsduihjfgsadygfuyshui" };
	char* go = "hello word";
	char* rs = "chnwsduihjfgsadygfuyshui";
	printf("标准库：%s\n", strcpy(to, go));
	strcpy(to, rs);
	printf("初代版：%s\n", my_strcpy_0(to, go));
	strcpy(to, rs);
	printf("优化版：%s\n", my_strcpy_1(to, go));
	strcpy(to, rs);
	printf("仿标准库版：%s\n", my_strcpy(to, go));
	strcpy(to, rs);

	return 0;
}