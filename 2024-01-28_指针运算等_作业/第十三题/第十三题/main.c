#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.1
 * 【完成日期】：	2024年  4月19日
 * 【更新内容】：优化掉了多余功能，减轻了硬件负担
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.0
 * 【历史日期】：	2024年  4月10日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】： 输入一个整数数组，实现一个函数，
				来调整该数组中数字的顺序使得数组中所有的奇数位于数组的前半部分，
				所有偶数位于数组的后半部分。
*******************************************************************************************/
#include<stdio.h>
#include<assert.h>

//排序函数
int sort(int* const p, int sz)//const修饰指针变量，防止其指向位置发生变化
{
	assert(p != NULL);//断言野指针
	int* p_agency = p;//定义代理指针，为可能的直接性地址改变做准备
	int* left = p;
	int* right = p + sz - 1;
	while (left < right)
	{
		while (*left % 2 != 0)
		{
			left++;
		}
		while (*right % 2 == 0)
		{
			right--;
		}
		int tmp = 0;
		tmp = *(left);
		*(left) = *(right);
		*(right) = tmp;
	}
}


//数组初始化函数
int input(int* const p_import, int sz)//const修饰指针变量，防止其指向位置发生变化
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;//数据预复位
	int i = 0;
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		int push = 0;
		push = scanf("%d", (p + i));
		if (push == EOF)
		{
			return EOF;//输入失败，返回EOF
		}
		else
		{
			j += push;
		}
	}
	return j;//正常运行返回读取个数
}

//数组打印函数
int print(int* const p_import, int sz)//const修饰指针变量，防止其指向位置发生变化
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;//指针预复位
	int i = 0;
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		int push = 0;
		push = printf("%d ", *(p + i));
		if (push < 0)
		{
			return EOF;//打印失败，返回EOF
		}
		else
		{
			j += push;
		}
	}
	printf("\n");
	return j;//正常运行返回输出个数
}


//主函数
//请勿使用UTF-8汉字编码
int main()
{
	int arr[10] = { 0 };
	int sz = 0;
	int push = 0;
	int i = 0;
	sz = sizeof(arr) / sizeof(arr[0]);
	int(*p[4])(int*, int) = { 0, input, sort, print };
	while (push != EOF)
	{
		i = 1;
		int x = 0;
		int y = 0;
		int z = 0;
		for (i = 1; i < 4; i++)
		{
			switch (i)
			{
			case 1:
				printf("请输入数组元素）(10个元素)：\n");
				x = (*p[i])(arr, sz);
				break;
			case 2:
				y = (*p[i])(arr, sz);
				break;
			case 3:
				printf("这是排列后的数组：\n");
				z = (*p[i])(arr, sz);
				break;
			}
			if (x == EOF || y == EOF || z == EOF)
			{
				push = EOF;
			}
		}
		printf("\n");

	}
	return 0;
}


#if 0
V1.0内容：
#include<stdio.h>
#include<assert.h>

//排序函数
int sort(int* const p_import, int sz)//const修饰指针变量，防止其指向位置发生变化
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 0; i < sz; i++)//遍历数组，检查偶数个数
	{
		if (*(p + i) % 2 == 0)
		{
			count++;
		}
	}
	while (count)
	{
		int store = 0;
		for (i = j; i < sz; i++)//遍历数组，找出并储存偶数
		{
			if (*(p + i) % 2 == 0)
			{
				j = i;//数据复位
				store = *(p + i);
				count--;
				break;
			}
		}
		while (i < sz - 1)//将之后元素向前位
		{
			*(p + i) = *(p + i + 1);
			i++;
		}
		*(p + sz - 1) = store;//把偶数放置在最后
	}
	return 0;//代表程序正常返回
}

//数组初始化函数
int input(int* const p_import, int sz)//const修饰指针变量，防止其指向位置发生变化
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;//数据预复位
	int i = 0;
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		int push = 0;
		push = scanf("%d", (p + i));
		if (push == EOF)
		{
			return EOF;//输入失败，返回EOF
		}
		else
		{
			j += push;
		}
	}
	return j;//正常运行返回读取个数
}

//数组打印函数
int print(int* const p_import, int sz)//const修饰指针变量，防止其指向位置发生变化
{
	assert(p_import != NULL);//野指针断言
	int* p = p_import;//指针预复位
	int i = 0;
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		int push = 0;
		push = printf("%d ", *(p + i));
		if (push < 0)
		{
			return EOF;//打印失败，返回EOF
		}
		else
		{
			j += push;
		}
	}
	printf("\n");
	return j;//正常运行返回输出个数
}


//主函数
//请勿使用UTF-8汉字编码
int main()
{
	int arr[10] = { 0 };
	int sz = 0;
	int push = 0;
	int i = 0;
	sz = sizeof(arr) / sizeof(arr[0]);
	int(*p[4])(int*, int) = { 0, input, sort, print };
	while (push != EOF)
	{
		i = 1;
		int x = 0;
		int y = 0;
		int z = 0;
		for (i = 1; i < 4; i++)
		{
			switch (i)
			{
			case 1:
				printf("请输入数组元素）(10个元素)：\n");
				x = (*p[i])(arr, sz);
				break;
			case 2:
				y = (*p[i])(arr, sz);
				break;
			case 3:
				printf("这是排列后的数组：\n");
				z = (*p[i])(arr, sz);
				break;
			}
			if (x == EOF || y == EOF || z == EOF)
			{
				push = EOF;
			}
		}
		printf("\n");
		/*char c_tmp;
		while ((c_tmp = getch() != '\n')  && c_tmp != EOF);*/ //不要清除缓冲区会卡死
	}
	return 0;
}
#endif