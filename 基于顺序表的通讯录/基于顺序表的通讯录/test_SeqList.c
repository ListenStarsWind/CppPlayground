#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
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
 * 【程序内容】：
 *******************************************************************************************/
#ifndef TEST_SEQLIST

#include"SeqList.h"

//功能测试
//Functional Testing
void FT(void)
{
	SeqList t;
	SeqListInit(&t);

	SeqListInsertAtPosition(&t, 0, 4);
	//4
	SeqListInsertAtPosition(&t, 0, 3);
	//3 4
	SeqListInsertAtPosition(&t, 0, 1);
	//1 3 4
	SeqListInsertAtPosition(&t, t.datacount, 7);
	//1 3 4 7
	SeqListInsertAtPosition(&t, t.datacount, 9);
	//1 3 4 7 9
	SeqListInsertAtPosition(&t, 1, 2);
	//1 2 3 4 7 9
	SeqListInsertAtPosition(&t, 4, 5);
	//1 2 3 4 5 7 9
	SeqListInsertAtPosition(&t, 5, 6);
	//1 2 3 4 5 6 7 9
	SeqListInsertAtPosition(&t, 7, 8);
	//1 2 3 4 5 6 7 8 9
	SeqListDeleteAtPosition(&t, 3);
	//1 2 3 5 6 7 8 9
	SeqListDeleteAtPosition(&t, 4);
	//1 2 3 5 7 8 9
	SeqListDeleteAtPosition(&t, 0);
	//2 3 5 7 8 9
	SeqListDeleteAtPosition(&t, t.datacount - 1);
	//2 3 5 7 8
	SeqListInsertAtBeginning(&t, 1);
	//1 2 3 5 7 8
	SeqListInsertAtBeginning(&t, 0);
	//0 1 2 3 5 7 8
	SeqListInsertAtEnd(&t, 9);
	//0 1 2 3 5 7 8 9
	SeqListInsertAtEnd(&t, 10);
	//0 1 2 3 5 7 8 9 10
	SeqListDeleteAtBeginning(&t);
	//1 2 3 5 7 8 9 10
	SeqListDeleteAtBeginning(&t);
	//2 3 5 7 8 9 10
	SeqListDeleteAtEnd(&t);
	//2 3 5 7 8 9
	int i = 0;
	i = SeqListSearch(&t, 5);
	if (i >= 0)
	{
		//找到了，下标为
		printf("Found it, the index is %d\n", i);
	}
	else
	{
		//找不到
		printf("Cannot be found\n");
	}
	i = SeqListSearch(&t, 0);
	if (i >= 0)
	{
		//找到了，下标为
		printf("Found it, the index is %d\n", i);
	}
	else
	{
		//找不到
		printf("Cannot be found\n");
	}
	SeqListDisplay(&t);
	SeqListDestroy(&t);
}

#define CASE(number,statement) case number: statement; break

//异常测试
//Negative Testing
void NT(void)
{
	int i = 0;
	if (scanf("%d", &i) != 1)
	{
		//输入错误
		printf("Input error.\n");
	}
	switch (i)
	{
		CASE(0, SeqListInit(NULL));
		CASE(1, SeqListDestroy(NULL));
		CASE(2, SeqListInsertAtPosition(NULL, 0, 0));
		CASE(3, SeqListDeleteAtPosition(NULL, 0));
		CASE(4, SeqListInsertAtBeginning(NULL, 0));
		CASE(5, SeqListInsertAtEnd(NULL, 0));
		CASE(6, SeqListDeleteAtBeginning(NULL));
		CASE(7, SeqListDeleteAtEnd(NULL));
		CASE(8, SeqListSearch(NULL, 0));
		CASE(9, SeqListDisplay(NULL));
		CASE(10, ;);
	}
	SeqList t;
	SeqListInit(&t);

	SeqListInsertAtPosition(&t, 0, 4);
	//4
	SeqListInsertAtPosition(&t, 0, 3);
	//3 4
	SeqListInsertAtPosition(&t, 0, 1);
	//1 3 4
	SeqListInsertAtPosition(&t, t.datacount, 7);
	//1 3 4 7
	SeqListInsertAtPosition(&t, 5, 4);
	SeqListInsertAtPosition(&t, -1, 4);
	SeqListDeleteAtPosition(&t, 4);
	SeqListDeleteAtPosition(&t, -1);
	SeqListDeleteAtBeginning(&t);
	SeqListDeleteAtBeginning(&t);
	SeqListDeleteAtBeginning(&t);
	SeqListDeleteAtBeginning(&t);
	SeqListDeleteAtBeginning(&t);
	SeqListInsertAtPosition(&t, 0, 4);
	//4
	SeqListInsertAtPosition(&t, 0, 3);
	//3 4
	SeqListDeleteAtEnd(&t);
	SeqListDeleteAtEnd(&t);
	SeqListDeleteAtEnd(&t);
	SeqListDestroy(&t);
}

//不用的宏及时移除，防止出错
//Unused macros should be promptly removed to prevent errors
#undef CASE

#define HISTORY(number) void history##number(void) \
		{\
				SeqList t;                            \
			SeqListInit(&t);                          \
			SeqListInsertAtPosition(&t, t.datacount, number);   \
			SeqListDisplay(&t);                       \
			SeqListDestroy(&t);                       \
		}

HISTORY(0)
HISTORY(1)
HISTORY(2)
HISTORY(3)

#undef HISTORY

int main()
{
	//FT();
	//NT();
	history3();
	return 0;
}
#endif