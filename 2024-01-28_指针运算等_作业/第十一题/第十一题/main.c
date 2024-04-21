#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.2
 * 【完成日期】：	2024年  4月日
 * 【更新内容】：修复了不能多次输入的BUG，以及三个方法连续调用的字符串复位问题
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.1
 * 【完成日期】：	2024年  4月16日
 * 【更新内容】：优化了底层运行逻辑，更正了错误理解
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.0
 * 【历史日期】：	2024年  4月9日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：实现一个函数，可以左旋字符串中的k个字符。
 *              例如：ABCD左旋一个字符得到BCDA，ABCD左旋两个字符得到CDAB。
 *******************************************************************************************/
#include<stdio.h>
#include<assert.h>
#include<string.h>



 //共有三种方法。

 //方法一：逐个旋转，可以看下面举的例子，abcd左旋2位得到cdab,cdab也可以由bcda左旋1位得到
//方法一 字符串的大小没有限制
void spin_left1(char str[], int n)
{
	int len = strlen(str);//放心使用strlen()不管是数组还是指针都可以使用，且包含空格，不包含‘\0’
	int logic = n % len;//计算逻辑旋转次数
	int i = 0;
	int j = 0;
	for (i = 0; i < logic; i++)
	{
		char push = str[0];
		for (j = 0; j < len - 1; j++)
		{
			str[j] = str[j + 1];
		}
		str[len - 1] = push;
	}
}

//方法二：调用两个库函数 strcpy 和 strcant(或者说是strncat)
//strcpy的形参是两个储存字符串的载体，它会把后一个载体中的字符串赋给前一个字符串的载体（比如数组，指针），用来拷贝字符串
//例如：
//#include<string.h>  strcpy头文件
//int main()
//{
//	char arr1[20] = "hello word";
//	char arr2[20] = "I am a student";
//	strcpy(arr1, arr2);
//	printf("%s", arr1);
//	return 0;
//}
//cmd显示：I am a student

//strncat是strcat的变形，strcat的形参也是两个字符型数组，如果把strcpy比作赋值号“=”，那strcat就相当于“+=”，用来拼接字符串
//#include<string.h>  strcat头文件
//int main()
//{
//	char arr1[30] = "hello word";
//	char* str = "I am a student";
//	strcat(arr1, str);
//	printf("%s", arr1);
//	return 0;
//}
//cmd显示：hello wordI am a student

//strcat是完全拼接，而strncat是不完全拼接，相比strcat,strncat多了一个整型形参，用来描述不完全的程度
//#include<string.h>  strncat头文件
//int main()
//{
//	char arr1[30] = "hello word";
//	char* str = "I am a student";
//	strncat(arr1, str, 4);
//	printf("%s", arr1);
//	return 0;
//}
//cmd显示：hello wordI am     I am的长度不就是四吗？
//需要注意的是使用它们都需要注意数组大小，比如若将第二个示例main函数中的30改为20，arr1就存不下hello wordI am a student了

//方法二 有字符串的大小限制
void spin_left2(char str[], int n)
{
	int len = strlen(str);//放心使用strlen()不管是数组还是指针都可以使用，且包含空格，不包含‘\0’
	int logic = n % len;//计算逻辑旋转次数
	char str_push[256] = { '0' };
	strcpy(str_push, str + logic);//数组名不就是地址吗？如果str中存的是abcd，那么str+2不就是cd吗
	strncat(str_push, str, logic);
	strcpy(str, str_push);
}

//第三种方法：三段倒置法
//还是对abcd来说
//右旋2位就是
//先倒置前两位：ba
//再倒置后面的：dc
//现在变成badc
//最后再整体倒置：cdab

//下面是倒置函数：
//start是开始下标，ending是结束下标
void changeover(char str[], int start, int ending)
{
	int left = start;
	int right = ending;
	for (; left < right; left++, right--)
	{
		char tmp = str[left];
		str[left] = str[right];
		str[right] = tmp;
	}
}

//下面是方法三本体
//方法三字符串长度没有限制
void spin_left3(char str[], int n)
{
	int len = strlen(str);//放心使用strlen()不管是数组还是指针都可以使用，且包含空格，不包含‘\0’
	int logic = n % len;//计算逻辑旋转次数
	changeover(str, 0, logic - 1);
	changeover(str, logic, len - 1);
	changeover(str, 0, len - 1);
}

//库函数fgets有三个参数，第一个参数是用来储存字符串的载体，第二个参数限制读取的字符串长度，第三个参数规定字符串的输入方式，
//若是用键盘读取或者说从缓冲区中读取，则是stdin（标准输入流）。参考资料：http://t.csdnimg.cn/XF4Z4
int main()
{
	void (*p[4])(char[], int) = { 0, spin_left1, spin_left2, spin_left3 };
	char arr[256] = { '0' };
	int mov = 0;
	char buffer[256]; // 改动：用于读取多余的输入
	while ((printf("请输入字符串，注意字符串长度不要超过256个字节:\n") > 0) && (fgets(arr, 256, stdin) != NULL)
		&& (printf("请输入右旋位数：\n") > 0) && (scanf("%d", &mov) == 1))
	{
		fgets(buffer, sizeof(buffer), stdin); // 清除多余的输入
		size_t len = strlen(arr);
		if (arr[len - 1] == '\n') {
			arr[len - 1] = '\0';
		}

		int i = 0;
		char arr_reset[256] = { '0' };
		strcpy(arr_reset, arr);
		for (i = 1; i < 4; i++)
		{
			switch (i)
			{
			case 1:
				printf("下面是第一种方法：\n");
				(*p[i])(arr, mov);
				printf("右旋结果：\n%s\n", arr);
				strcpy(arr, arr_reset);
				break;
			case 2:
				printf("下面是第二种方法：\n");
				(*p[i])(arr, mov);
				printf("右旋结果：\n%s\n", arr);
				strcpy(arr, arr_reset);
				break;
			case 3:
				printf("下面是第三种方法：\n");
				(*p[i])(arr, mov);
				printf("右旋结果：\n%s\n", arr);
				strcpy(arr, arr_reset);
				break;
			}
		}
		printf("\n");
	}
	return 0;
}


#if 0
============================================================================================ =
下面是V1.1的main函数部分
//主函数
int main()
{
	void (*p[4])(char[], int) = { 0, spin_left1, spin_left2, spin_left3 };
	char arr[256] = { '0' };
	int mov = 0;
	while ((0 < printf("请输入字符串，注意字符串长度不要超过256个字节:\n")) && (EOF != gets(arr))
		&& (0 < printf("请输入右旋位数：\n")) && (scanf("%d", &mov)))
	{
		int i = 0;
		char arr_reset[256] = { '0' };
		strcpy(arr_reset, arr);
		for (i = 1; i < 4; i++)
		{
			switch (i)
			{
			case 1:
				printf("下面是第一种方法：\n");
				(*p[i])(arr, mov);
				printf("右旋结果：\n%s\n", arr);
				strcpy(arr, arr_reset);
				break;
			case 2:
				printf("下面是第二种方法：\n");
				(*p[i])(arr, mov);
				printf("右旋结果：\n%s\n", arr);
				strcpy(arr, arr_reset);
				break;
			case 3:
				printf("下面是第三种方法：\n");
				(*p[i])(arr, mov);
				printf("右旋结果：\n%s\n", arr);
				strcpy(arr, arr_reset);
				break;
			}
		}
		printf("\n");
	}
	return 0;
}

============================================================================版本分隔符
错误理解指的是1.0我认为必须旋转少于字符串长度的数，但实际是可以超过：
举个例子：对于abcd，
左旋1位是bcda
左旋2位是cdab
左旋3位是dabc
左旋4位是abcd
左旋5位是bcda
左旋6位是cdab
左旋7位是dabc

V1.0内容：
//spin_1输入字符串地址，左旋数目；
//注意字符串长度不得超过100；
//若左旋数目超出字符串长度，则返回EOF。
int spin_l(char* p_import, int move)
{
	assert(p_import != NULL);//野指针断言
	char* p = p_import;
	int count = 0;
	while (*p != '\0')
	{
		p++;
		count++;
	}
	p = p_import;
	if (move > count)//输入错误提示
	{
		return EOF;
	}
	int i = 0;
	int j = 0;
	char arr_push[100] = { '0' };
	for (i = 0; i < move; i++)//使用第三方数组储存要移动的字符串
	{
		arr_push[i] = *(p + i);
	}
	for (i = 0; i < (count - move); i++)//把剩下的字符串提到前面
	{
		*(p + i) = *(p + move + i);
	}
	for (i = (count - move), j = 0; i < count; i++, j++)//把储存的字符串移到后面
	{
		*(p + i) = arr_push[j];
	}
}

//程序允许多次输入，输入格式为：字符串 回车 左旋数目 回车
int main()
{
	char arr[100] = { '0' };
	while (EOF != scanf("%[^\n]", &arr))
	{
		int shirt = 0;
		int flag = 0;//放置返回值
		scanf("%d", &shirt);
		flag = spin_l(arr, shirt);
		if (flag == EOF)//判断是否输入错误
		{
			break;
		}
		printf("%s\n", arr);
		char c_tmp;
		while ((c_tmp = getchar() != '\n') && c_tmp != EOF);//清除缓冲区
	}
	printf("请检查您的输入是否有误，再重新运行程序");//请勿使用UTF-8汉字编码
	return 0;
}
#endif