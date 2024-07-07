#define _CRT_SECURE_NO_WARNINGS

#include"SList.h"

//单元测试0：测试函数CreateNode
//Unit Test 0: Test the CreateNode function
void test0()
{
	SListNode* SListHead = NULL;
	SListHead = CreateNode(0);
	assert(SListHead);
	printf("%d ", SListHead->data);
}

//单元测试1：测试函数SListPrintf
//Unit Test 1: Test the SListPrintf function
void test1()
{
	SListNode* SListHead = NULL;
	SListHead = CreateNode(0);
	assert(SListHead);
	SListNode* SListTemp = NULL;
	SListTemp = CreateNode(1);
	assert(SListTemp);
	SListHead->next = SListTemp;
	SListTemp = CreateNode(2);
	assert(SListTemp);
	SListHead->next->next = SListTemp;
	SListPrintf(SListHead);
}

//单元测试2：测试函数InsertTail
//Unit Test 2: Test the InsertTail function
void test2()
{
	SListNode* SListHead = NULL;
	InsertTail(&SListHead, 0);
	InsertTail(&SListHead, 1);
	InsertTail(&SListHead, 2);
	InsertTail(&SListHead, 3);
	SListPrintf(SListHead);
}


//单元测试3：测试函数InsertHead
//Unit Test 3: Test the InsertHead function
void test3()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 2);
	InsertHead(&SListHead, 1);
	InsertHead(&SListHead, 0);
	SListPrintf(SListHead);
}

//单元测试4：测试函数DelateTail
//Unit Test 4: Test the DelateTail function
void test4_0()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 2);
	InsertHead(&SListHead, 1);
	InsertHead(&SListHead, 0);
	SListPrintf(SListHead);
	DelateTail(&SListHead);
	SListPrintf(SListHead);
	DelateTail(&SListHead);
	SListPrintf(SListHead);
	DelateTail(&SListHead);
	SListPrintf(SListHead);
	DelateTail(&SListHead);
	SListPrintf(SListHead);

}
void test4_1()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 2);
	InsertHead(&SListHead, 1);
	InsertHead(&SListHead, 0);
	SListPrintf(SListHead);
	while (DelateTail(&SListHead) != EOF)
	{
		;
	}
	SListPrintf(SListHead);
}

//单元测试5：测试函数DelateHead
//Unit Test 5: Test the DelateHead function
void test5()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 2);
	InsertHead(&SListHead, 1);
	InsertHead(&SListHead, 0);
	SListPrintf(SListHead);
	DelateHead(&SListHead);
	SListPrintf(SListHead);
	DelateHead(&SListHead);
	SListPrintf(SListHead);
	DelateHead(&SListHead);
	SListPrintf(SListHead);
	DelateHead(&SListHead);
	SListPrintf(SListHead);
}

//单元测试6：测试函数FindNode
//Unit Test 6: Test the FindNode function
void test6()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 2);
	InsertHead(&SListHead, 1);
	InsertHead(&SListHead, 0);
	SListPrintf(SListHead);
	SListNode* PtrTemp = FindNode(SListHead, 5);
	if (PtrTemp)
	{
		SListPrintf(PtrTemp);
	}
	else
	{
		printf("cannot find\n");
	}
}

//单元测试7：测试函数DePosi
//Unit Test 7: Test the DePosi function
void test7()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 2);
	InsertHead(&SListHead, 1);
	InsertHead(&SListHead, 0);
	SListPrintf(SListHead);
	SListNode* TempNode = FindNode(SListHead, 3);
	DePosi(&SListHead, TempNode);
	SListPrintf(SListHead);
	InsertTail(&SListHead, 3);
	TempNode = FindNode(SListHead, 0);
	DePosi(&SListHead, TempNode);
	SListPrintf(SListHead);
	TempNode = FindNode(SListHead, 2);
	DePosi(&SListHead, TempNode);
	SListPrintf(SListHead);
}

//单元测试8：测试函数InBefoPosi
//Unit Test 8: Test the InBefoPosi function
void test8()
{
	SListNode* SListHead = NULL;
	InsertHead(&SListHead, 3);
	InsertHead(&SListHead, 1);
	SListPrintf(SListHead);
	SListNode* TempNode = FindNode(SListHead, 3);
	InBefoPosi(&SListHead, TempNode, 2);
	SListPrintf(SListHead);
	TempNode = FindNode(SListHead, 1);
	InBefoPosi(&SListHead, TempNode, 0);
	SListPrintf(SListHead);
}

int main()
{
	test8();
	return 0;
}