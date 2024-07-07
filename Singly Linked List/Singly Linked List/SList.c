#define _CRT_SECURE_NO_WARNINGS
/******************************************************************************************
* 【文件名称】：SList.c
* 【文件标识】：
* =========================================================================================
* 【当前作者】：听风若依
* 【当前版本】：1.0
* 【完成日期】：2024年 月日
* 【更新内容】：
* =========================================================================================
* 【历史作者】：听风若依
* 【历史版本】：V1.
* 【历史日期】：2024年 月日
* =========================================================================================
* 【开发平台】：VS2022
* 【程序功能】：
* =========================================================================================*/
#include"SList.h"

SListNode* CreateNode(SListDataType data)
{
	SListNode* Ptr = (SListNode*)malloc(sizeof(SListNode));
	assert(Ptr);
	Ptr->data = data;
	Ptr->next = NULL;
	return Ptr;
}

void SListPrintf(SListNode* PtrHead)
{
	SListNode* PtrTrav = PtrHead;
	while (PtrTrav)
	{
		printf("%d->", PtrTrav->data);
		PtrTrav = PtrTrav->next;
	}
	printf("NULL\n");
}

void InsertTail(SListNode** PPtrHead, SListDataType x)
{
	assert(PPtrHead);
	SListNode* PtrTrav = *PPtrHead;
	SListNode* NewNode = CreateNode(x);
	if (PtrTrav == NULL)
	{
		*PPtrHead = NewNode;
	}
	else
	{
		while (PtrTrav->next)
		{
			PtrTrav = PtrTrav->next;
		}
		PtrTrav->next = NewNode;
	}
}

void InsertHead(SListNode** PPtrHead, SListDataType x)
{
	assert(PPtrHead);
	SListNode* NewNode = CreateNode(x);
	NewNode->next = *PPtrHead;
	*PPtrHead = NewNode;
}

int DelateTail(SListNode** PPtrHead)
{
	assert(PPtrHead);
	if (*PPtrHead == NULL)
	{
		return EOF;
	}
	if ((*PPtrHead)->next == NULL)
	{
		free(*PPtrHead);
		*PPtrHead = NULL;
	}
	else
	{
		SListNode* PtrTarget = *PPtrHead;
		SListNode* PtrLast = *PPtrHead;
		while (PtrTarget->next)
		{
			PtrLast = PtrTarget;
			PtrTarget = PtrTarget->next;
		}
		free(PtrTarget);
		PtrTarget = NULL;
		PtrLast->next = PtrTarget;
	}
	return 0;
}

int DelateHead(SListNode** PPtrHead)
{
	assert(PPtrHead);
	if (*PPtrHead == NULL)
	{
		return EOF;
	}
	SListNode* PtrTemp = (*PPtrHead)->next;
	free(*PPtrHead);
	*PPtrHead = PtrTemp;
	return 0;
}

SListNode* FindNode(SListNode* PtrHead, SListDataType x)
{
	SListNode* PtrTemp = PtrHead;
	while (PtrTemp != NULL && PtrTemp->data != x)
	{
		PtrTemp = PtrTemp->next;
	}
	return PtrTemp;
}

void InBefoPosi(SListNode** PPtrHead, SListNode* TargetPtr, SListDataType x)
{

}

void  DePosi(SListNode** PPtrHead, SListNode* TargetPtr)
{
	SListNode* TempPtr = *PPtrHead;
	SListNode* LastPtr = *PPtrHead;
	while (TempPtr != TargetPtr && TempPtr != NULL)
	{
		LastPtr = TempPtr;
		TempPtr = TempPtr->next;
	}
	if (TempPtr == *PPtrHead)
	{
		*PPtrHead = TempPtr->next;
		free(TempPtr);
		TempPtr = NULL;
	}
	else if (TempPtr != NULL)
	{
		LastPtr->next = TempPtr->next;
		free(TempPtr);
		TempPtr = NULL;
	}
	else
	{
		printf("Target does not exist\n");
	}
}