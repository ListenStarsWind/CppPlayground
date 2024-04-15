#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  4月15日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：写一个函数，判断一个字符串是否为另外一个字符串旋转之后的字符串。
 *******************************************************************************************/
 //例如：给定s1 = AABCD和s2 = BCDAA，返回1
 //给定s1 = abcd和s2 = ACBD，返回0.
 //AABCD左旋一个字符得到ABCDA
 //AABCD左旋两个字符得到BCDAA
 //AABCD右旋一个字符得到DAABC
#include<stdio.h>
#include<assert.h>

//计算字符串函数
int my_strlen(const char* const p_import)//使用const修饰指针及其指向内容，防止它们遭到非法篡改
{
	assert(p_import != EOF);//断言野指针
	char* p = p_import;//指针预复位
	int i = 0;
	int count = 0;
	while ('\0' != *(p + i))
	{
		count++;
		i++;
	}
	return count;
}

//互旋字符串判断函数
int rotation(const char* const S1_import, const char* const S2_import)//使用const修饰指针及其指向内容，防止它们遭到非法篡改
{
	assert(S1_import != EOF);
	assert(S2_import != EOF);//断言野指针
	char* S1 = S1_import;
	char* S2 = S2_import;//指针预复位
	if (my_strlen(S1) == my_strlen(S2))
	{
		int len_ch = my_strlen(S1);
		int a = 0;
		int flag = 0;
		for (a = 0; a < len_ch; a++)
		{
			if (*(S1 + a) != *(S2 + a))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			return 1;
		}
		else
		{
			int i = 0;
			int j = len_ch - 1;
			int k = 0;
			//左判断
			while (*(S1 + i) == *(S2 + j))
			{
				i++;
				j--;
			}
			while (*(S1 + i) == *(S2 + k) && *(S1 + i) != '\0')
			{
				i++;
				k++;
			}
			if (i == len_ch)
			{
				return 1;
			}

			i = 0;
			j = len_ch - 1;
			k = 0;          //变量复位
			//右判断
			while (*(S2 + i) == *(S1 + j))
			{
				i++;
				j--;
			}
			while (*(S2 + i) == *(S1 + k) && *(S1 + i) != '\0')
			{
				i++;
				k++;
			}
			if (i == len_ch)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

//主函数
int main()
{
	char* S1 = "abcd";
	char* S2 = "ABCD";
	int push = 0;
	push = rotation(S1, S2);
	if (push == 1)
	{
		printf("S1 and S2 are spin.\n");
	}
	else
	{
		printf("S1 and S2 are not spin.\n");
	}
	return 0;
}