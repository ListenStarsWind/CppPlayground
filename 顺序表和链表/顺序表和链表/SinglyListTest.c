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

int main()
{
	Test4();
	return 0;
}