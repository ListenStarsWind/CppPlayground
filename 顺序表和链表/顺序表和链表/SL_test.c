#define _CRT_SECURE_NO_WARNINGS

#include"SeqList.h"

#if CHOOSE_SINGIY

void SeqListTest1()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 1);
	SeqListPushBack(ps, 2);
	SeqListPushBack(ps, 3);
	SeqListPushBack(ps, 4);
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}

void SeqListTest2()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 3);
	SeqListPushFront(ps, 2);
	SeqListPushFront(ps, 1);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}

void SeqListTest3()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 3);
	SeqListPushFront(ps, 2);
	SeqListPushFront(ps, 1);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}

void SeqListTest4()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 3);
	SeqListPushFront(ps, 2);
	SeqListPushFront(ps, 1);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListDestroy(ps);
	ps = NULL;
}

void SeqListTest5()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 1);
	SeqListPrintf(ps);
	SeqListInsert(ps, 1, 3);
	SeqListInsert(ps,1,2);
	SeqListPrintf(ps);
	SeqListInsert(ps, 6, 7);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopFront(ps);
	SeqListDestroy(ps);
	ps = NULL; 
}

void SeqListTest6()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 1);
	SeqListPrintf(ps);
	SeqListInsert(ps, 1, 3);
	SeqListInsert(ps, 1, 2);
	SeqListPrintf(ps);
	SeqListInsert(ps, 6, 7);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListErase(ps, 2);
	SeqListErase(ps,2);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}

void SeqListTest7()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 1);
	SeqListPrintf(ps);
	SeqListInsert(ps, 1, 3);
	SeqListInsert(ps, 1, 2);
	SeqListPrintf(ps);
	SeqListInsert(ps, 6, 7);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListErase(ps, 2);
	SeqListErase(ps, 2);
	SeqListPrintf(ps);
	int pos = SeqListFind(ps, 6);
	if (pos)
	{
		SeqListModify(ps, pos, 9);
	}
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}

int main()
{
	SeqListTest7();
	return 0;
}

#endif