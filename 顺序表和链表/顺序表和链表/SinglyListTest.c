#define _CRT_SECURE_NO_WARNINGS

#include"SinglyList.h"

void Test1()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 1);
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 3);
	SinglyListPushFront(&PHead, 4);
	SinglyListPrintf(PHead);
}

void Test2()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 1);
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 3);
	SinglyListPushFront(&PHead, 4);
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}

void Test3()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 1);
	SinglyListPushBack(&PHead, 3);
	SinglyListPushBack(&PHead,4);
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}

void Test4()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 1);
	SinglyListPushBack(&PHead, 3);
	SinglyListPushBack(&PHead, 4);
	SinglyListPrintf(PHead);
	SinglyListPopFront(&PHead);
	SinglyListPrintf(PHead);
	SinglyListPopBack(&PHead);
	SinglyListPrintf(PHead);
	SinglyListPopBack(&PHead);
	SinglyListPrintf(PHead);
	SinglyListPopBack(&PHead);
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}

void Test5()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushBack(&PHead, 4);
	SinglyListPushFront(&PHead, 1);
	SinglyListPrintf(PHead);
	PSinglyListNode pos = SinglyListFind(PHead, 1);
	if (pos)
	{
		SinglyInsert(NULL, pos, 2);
	}
	else
	{
		printf("Find fail!\n");
	}
	pos = SinglyListFind(PHead, 4);
	if (pos)
	{
		SinglyInsert(&PHead, pos, 3);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	SinglyListPopFront(&PHead);
	SinglyListPopBack(&PHead);
	SinglyListPopFront(&PHead);
	SinglyListPrintf(PHead);
	pos = SinglyListFind(PHead, 3);
	if (pos)
	{
		SinglyInsert(&PHead, pos, 2);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}

void Test6()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushBack(&PHead, 4);
	SinglyListPushFront(&PHead, 1);
	SinglyListPrintf(PHead);
	PSinglyListNode pos = SinglyListFind(PHead, 1);
	if (pos)
	{
		SinglyErase(&PHead, pos);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	pos = SinglyListFind(PHead, 4);
	if (pos)
	{
		SinglyErase(&PHead, pos);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}

int main()
{
	Test6();
	return 0;
}