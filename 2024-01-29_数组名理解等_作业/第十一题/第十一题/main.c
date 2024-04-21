#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.1
 * 【完成日期】：	2024年  4月19日
 * 【更新内容】：优化了运行逻辑，1.0逻辑太垃圾了
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.0
 * 【历史日期】：	2024年  4月15日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：写一个函数，判断一个字符串是否为另外一个字符串旋转之后的字符串。
 *******************************************************************************************/
 //例如：给定s1 = AABCD和s2 = BCDAA，返回1
 //给定s1 = abcd和s2 = ACBD，返回0.
 //AABCD左旋一个字符得到ABCDA
 //AABCD左旋两个字符得到BCDAA
 //AABCD右旋一个字符得到DAABC

//共两种方法：
//方法一：对其中一个字符串一位一位地旋转，每旋转一次，与另一个字符串比对

#include<stdio.h>
#include<assert.h>
#include<string.h>

//互旋字符串判断函数
//需要用到库函数strcmp and strstr
//strcmp有两个形参，这两个形参都是字符串；
//strcmp将比较这两个字符串的大小；
//字符串的大小如何比较？
//逐位比较对应字符的ASCll的值，
//比如字符串S1==abcd 字符串S2==abce
//先比较它们的第一位：S1第一位是a a的ASCll值为97，S2第一位是a a的ASCll值为97，97 == 97，跳到下一位
//                  S1第二位是b b的ASCll值为98，S2第二位是b b的ASCll值为98，98 == 98, 跳到下一位
//                  S1第三位是c c的ASCll值为99，S2第三位是c c的ASCll值为99，99 == 99, 跳到下一位
//                  S1第四位是d d的ASCll值为100，S2第四位是e e的ASCll值为101，100 < 101, 则S1 < S2;

//比如字符串S1==abc 字符串S2==abce
//先比较它们的第一位：S1第一位是a a的ASCll值为97，S2第一位是a a的ASCll值为97，97 == 97，跳到下一位
//                  S1第二位是b b的ASCll值为98，S2第二位是b b的ASCll值为98，98 == 98, 跳到下一位
//                  S1第三位是c c的ASCll值为99，S2第三位是c c的ASCll值为99，99 == 99, 跳到下一位
//                  S1没有第四位，而S2有第四位， 则S1 < S2;

//而对于strcmp来说，若调用形式为strcmp(S1, S2),
//若S1 < S2 返回负数
//若S1 == S2 返回0
//若S1 > S2 返回正数

//方法一：
//字符串左旋判断函数
//若是互旋字符串，返回1，否则返回0.
int rotation_left(char S1[], char S2[])
{
	int i = 0;
	int j = 0;
	int len = strlen(S1);
	for (i = 0; i < len; i++)
	{
		char push = S1[0];
		for (j = 0; j < len - 1; j++)
		{
			S1[j] = S1[j + 1];
		}
		S1[len - 1] = push;
		if (strcmp(S1, S2) == 0)
		{
			return 1;
		}
	}
	return 0;
}

//字符串右旋判断函数
//若是互旋字符串，返回1，否则返回0.abcd dabc
int rotation_right(char S1[], char S2[])
{
	int i = 0;
	int j = 0;
	int len = strlen(S1);
	for (i = 0; i < len; i++)
	{
		char push = S1[len - 1];
		for (j = len - 2; j >= 0; j--)
		{
			S1[j + 1] = S1[j];
		}
		S1[0] = push;
		if (strcmp(S1, S2) == 0)
		{
			return 1;
		}
	}
	return 0;
}

//abcd cdab abcdabcd
//abcd dabc cdab abcdabcd
//方法二：使用库函数strstr
//头文件还是string.h
//strstr有两个参数，都是字符串，形如strstr(S1, S2) 他会在S1中寻找S2，比如S1== abcdabcd  S2 = cdab 
//这种就是找得到的，要是S2 == cdabf,可就找不到了。
//如果找到所搜索的字符串，则该函数返回第一次匹配的字符串的地址；
//如果未找到所搜索的字符串，则返回NULL。

int rotation(char S1[], char S2[])
{
	int push = 0;
	strcat(S1, S1);
	push = strstr(S1, S2);
	if (push != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//主函数
int main()
{
	char S1[256] = { "abcd" };
	char* S2 = "cdab";
	int i = 0;
	int j = 0;
	int k = 0;
	i = rotation_left(S1, S2);
	j = rotation_right(S1, S2);
	k = rotation(S1, S2);
	if (i == 1 || j == 1)
	{
		printf("S1 and S2 are spin.\n");
	}
	else
	{
		printf("S1 and S2 are not spin.\n");
	}
	return 0;
}

#if 0
V1.0内容
#include<stdio.h>
#include<assert.h>

//计算字符串函数
int my_strlen(const char* const p_import)//使用const修饰指针及其指向内容，防止它们遭到非法篡改
{
	assert(p_import != NULL);//断言野指针
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

int main()
{

	return 0;
}

//互旋字符串判断函数
int rotation(const char* const S1_import, const char* const S2_import)//使用const修饰指针及其指向内容，防止它们遭到非法篡改
{
	assert(S1_import != NULL);
	assert(S2_import != NULL);//断言野指针
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
#endif