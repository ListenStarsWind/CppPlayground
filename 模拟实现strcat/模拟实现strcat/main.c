#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：main.c
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
 * 【程序内容】：模拟实现strcat
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>
#include<string.h>

char* my_strcat(char* destination, const char* source)
{
	assert(destination && source);
	char* ret = destination;
	while (*destination)
	{
		destination++;
	}
	while (*destination++ = *source++)
	{
		;
	}
	return ret;
}

int main()
{
	char to[50] = "hello ";
	char* go = "word";
	char* rs = "hello ";
	printf("%s\n", strcat(to, go));
	strcpy(to, rs);
	printf("%s\n", my_strcat(to, go));
	strcpy(to, rs);
	return 0;
}