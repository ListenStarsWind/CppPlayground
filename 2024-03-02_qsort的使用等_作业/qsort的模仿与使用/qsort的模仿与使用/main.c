#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  4月25日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：以冒泡排序为底层逻辑，构建自己的qsort函数并使用
 *******************************************************************************************/
#include<stdio.h>
#include<string.h>

struct 英桀
{
	char name[20];
	char 刻印[20];
	char 祝词[100];
};

//交换函数
void swap(size_t units, const void* p1, const void* p2)
{
	int i = 0;
	for (i = 0; i < units; i++)
	{
		char push = '0';
		push = *(((char*)p1) + i);
		*(((char*)p1) + i) = *(((char*)p2) + i);
		*(((char*)p2) + i) = push;
	}
}

//比较函数char
int cmp_char(const void* p1, const void* p2)
{
	return strcmp(*((char*)p1), *((char*)p2));
}

//比较函数int
int cmp_int(const void* p1, const void* p2)
{
	return *(int*)p1 - *(int*)p2;
}

int cmp_英桀_name(const void* p1, const void* p2)
{
	return strcmp(((struct 英桀*)p1)->name, ((struct 英桀*)p2)->name);
}


//冒泡排序升级版
void bubble_qsort(void* dat, size_t num, size_t units, int(*cmp)(const void* p1, const void* p2))
{
	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < num - 1; i++)
	{
		flag = 0;
		for (j = 0; j < num - 1 - i; j++)
		{
			if (cmp((char*)dat + j * units, (char*)dat + (j + 1) * units) > 0)
			{
				swap(units, (char*)dat + j * units, (char*)dat + (j + 1) * units);
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}

void print(struct 英桀 arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%s  ", (arr + i)->name);
		printf("%s  ", (arr + i)->刻印);
		printf("%s  ", (arr + i)->祝词);
		printf("\n");
		printf("\n");
	}
}

//test1
int test1(void)
{
	int arr[10] = { 1, 3, 9, 4, 2, 7, 5, 6, 8, 10 };
	size_t sz = 0;
	int i = 0;
	sz = sizeof(arr) / sizeof(arr[0]);
	bubble_qsort(arr, sz, sizeof(int), cmp_int);
	for (; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

//test2
int test2(void)
{
	/*struct 英桀 Ⅰ = { {"Kevin"}, {"救世"}, {"愿无烬之剑爱佑其身，赐予「救世」的理想。"} };
	struct 英桀 Ⅱ = { {"Elysia"}, {"真我"}, {"愿无瑕之人爱佑其身，赐予「真我」的回归。"} };
	struct 英桀 Ⅲ = { {"Aponia"}, {"戒律"}, {"愿深罪之槛爱佑其身，赐予「戒律」的慈爱。"} };
	struct 英桀 Ⅳ = { {"Eden"}, {"黄金"}, {"愿璀耀之歌爱佑其身，赐予「黄金」的光辉。"} };
	struct 英桀 Ⅴ = { {"Vill-V"}, {"螺旋"}, {"愿愚戏之匣爱佑其身，赐予「螺旋」的奇迹。"} };
	struct 英桀 Ⅵ = { {"Kalpas"}, {"鏖灭"}, {"愿坏劫之焱爱佑其身，赐予「鏖灭」的赤诚。"} };
	struct 英桀 Ⅶ = { {"Su"}, {"天慧"}, {"愿善法之瞳爱佑其身，赐予「天慧」的智识。"} };
	struct 英桀 Ⅷ = { {"Sakura"}, {"刹那"}, {"愿寸断之刃爱佑其身，赐予「刹那」的决绝。"} };
	struct 英桀 Ⅸ = { {"Kosma"}, {"旭光"}, {"愿黎明之哨爱佑其身，赐予「旭光」的意志。"} };
	struct 英桀 Ⅹ = { {"Mobius"}, {"无限"}, {"愿噬界之蛇爱佑其身，赐予「无限」的渴求。"}};
	struct 英桀 Ⅺ = { {"Griseo"}, {"繁星"}, {"愿绘世之卷爱佑其身，赐予「繁星」的纯真。"} };
	struct 英桀 Ⅻ = { {"Hua"}, {"浮生"}, {"愿渡尘之羽爱佑其身，赐予「浮生」的坚忍。"} };
	struct 英桀 ⅩⅢ = { {"Pardofelis"}, {"空梦"}, {"愿掠集之兽爱佑其身，赐予「空梦」的自由。"} };*/
	struct 英桀 逐火[13] = {
	{ {"Kevin"}, {"救世"}, {"愿无烬之剑爱佑其身，赐予「救世」的理想。"} } ,
	{ {"Elysia"}, {"真我"}, {"愿无瑕之人爱佑其身，赐予「真我」的回归。"} },
	{ { "Aponia" }, {"戒律"}, {"愿深罪之槛爱佑其身，赐予「戒律」的慈爱。"} },
	{ { "Eden" }, {"黄金"}, {"愿璀耀之歌爱佑其身，赐予「黄金」的光辉。"} },
	{ { "Vill-V" }, {"螺旋"}, {"愿愚戏之匣爱佑其身，赐予「螺旋」的奇迹。"} },
	{ { "Kalpas" }, {"鏖灭"}, {"愿坏劫之焱爱佑其身，赐予「鏖灭」的赤诚。"} },
	{ { "Su" }, {"天慧"}, {"愿善法之瞳爱佑其身，赐予「天慧」的智识。"} },
	{ { "Sakura" }, {"刹那"}, {"愿寸断之刃爱佑其身，赐予「刹那」的决绝。"} },
	{ { "Kosma" }, {"旭光"}, {"愿黎明之哨爱佑其身，赐予「旭光」的意志。"} },
	{ { "Mobius" }, {"无限"}, {"愿噬界之蛇爱佑其身，赐予「无限」的渴求。"} },
	{ { "Griseo" }, {"繁星"}, {"愿绘世之卷爱佑其身，赐予「繁星」的纯真。"} },
	{ { "Hua" }, {"浮生"}, {"愿渡尘之羽爱佑其身，赐予「浮生」的坚忍。"} },
	{ { "Pardofelis" }, {"空梦"}, {"愿掠集之兽爱佑其身，赐予「空梦」的自由。"} }
	};
	size_t sz = 0;
	int i = 0;
	sz = sizeof(逐火) / sizeof(逐火[0]);
	bubble_qsort(逐火, sz, sizeof(逐火[0]), cmp_英桀_name);
	print(逐火, sz);
	return 0;
}

int main()
{
	//test1();
	test2();
	return 0;
}

