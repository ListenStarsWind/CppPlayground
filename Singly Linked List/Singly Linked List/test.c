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
//Unit Test 1: Test the InsertTail function
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
//Unit Test 1: Test the InsertHead function
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
//Unit Test 1: Test the DelateTail function
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
//Unit Test 1: Test the DelateHead function
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

int main()
{
	test5();
	return 0;
}