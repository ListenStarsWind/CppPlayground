#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：test.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  月日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：负责测试各子模块
 *******************************************************************************************/
#include"SeqList.h"

void SLInit_test(void)
{
	SL s;
#ifndef __SLINT__

#ifdef __SLINT_DEBUG__

	SLInit(&s);

#else

	SLInit(NULL);

#endif

#else

	SLInit(s);

#endif
}

static SLprintf(SL* p)
{
	int i = 0;
	printf("\n");
	for (i = 0; i < p->size; i++)
	{
		printf("%d ", p->arr[i]);
	}
	printf("\n\n");
}

void SLPushBack_test(void)
{
	SL s;
	SLInit(&s);
	SLPushBack(&s, 1);
	SLPushBack(&s, 2);
	SLPushBack(&s, 3);
	SLPushBack(&s, 4);
	SLPushBack(&s, 5);
	SLPushBack(&s, 6);
	SLPushBack(&s, 7);
	SLPushFront(&s, 8);
	SLPushFront(&s, 9);
	SLPushFront(&s, 10);
	SLPushFront(&s, 11);
	SLPushFront(&s, 12);

	SLprintf(&s);
	SLPopFront(&s);
	SLPopFront(&s);
	SLPopFront(&s);
	SLPopFront(&s);
	SLPopFront(&s);
	SLPopFront(&s);
	SLPopFront(&s);

	SLPopFront(&s);
	SLPopFront(&s);
	SLprintf(&s);
	SLInsert(&s, 1, 4);
	SLErase(&s, 1);
	int a = SLFind(&s, 7);
	if (a < 0)
	{
		printf("找不到\n");
	}
	else
	{
		printf("找到了，下标为%d\n", a);
	}
	SLDestroy(&s);
}


int main()
{
	//SLInit_test();
	SLPushBack_test();
	return 0;
}
