#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.1
 * 【完成日期】：	2024年  4月9日
 * 【更新内容】：	修复了不能多组输入的bug。
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.0
 * 【历史日期】：	2024年 4月8日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：将一个字符串str的内容颠倒过来，并输出。数据范围：1<=len(str)<=10000(颇有难度)
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>

 //'0'是一个字符串结束的标志，通过此种方式统计字符串长度 
int my_strlen(const char* p)//指针变量用const修饰，防止指向内容遭到非法篡改
{
	assert(p != NULL);//野指针断言
	char* p_copy = p;
	while (*p_copy != '\0')
	{
		p_copy++;
	}
	return p_copy - p;
}

// 为了实现多组输入，使用
// char c_tmp;
// while ((c_tmp = getchar() != '\n') && c_tmp != EOF);
// 清除缓冲区。
int main()
{
	char arr[20] = { '0' };
	scanf("%[^\n]", &arr);

	int i = my_strlen(arr);
	printf("%d", i);
	/*char arr[10000] = { '0' };
	while (EOF != scanf("%[^\n]", arr))
	{
		int len = my_strlen(arr);
		int left = 0;
		int right = 0;
		int i = 0;
		for (left = 0, right = len - 1; left <= right; left++, right--)
		{
			char interchange = arr[left];
			arr[left] = arr[right];
			arr[right] = interchange;
		}
		printf("%s\n", arr);
		char c_tmp;
		while ((c_tmp = getchar() != '\n') && c_tmp != EOF);
	}*/
	return 0;
}
#if 0
//1.0内容：
int main()
{
	char arr[10000] = { '0' };
	scanf("%[^\n]", arr);
	int len = my_strlen(arr);
	int left = 0;
	int right = 0;
	int i = 0;
	for (left = 0, right = len - 1; left <= right; left++, right--)
	{
		char interchange = arr[left];
		arr[left] = arr[right];
		arr[right] = interchange;
	}
	printf("%s\n", arr);
	return 0;
}
#endif