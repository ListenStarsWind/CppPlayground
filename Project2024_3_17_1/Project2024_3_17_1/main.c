#define _CRT_SECURE_NO_WARNINGS
//这是一个测试属性的项目，功能是判断一个月份中的天数，采用多文件书写而成。
//与上一个项目的区别是，这次使用extern进行声明而不是include。
#include<stdio.h>
extern int day(int m, int y);
extern int int_leap(int m, int y);
int main()
{
	int mouth, year;
	printf("请输入您所选中的年份和月份，注意必须先输入月份再输入年份。\n");
	scanf("%d%d", &mouth, &year);
	printf("这个月份有%d天。\n", day(mouth, year));
	return 0;
}