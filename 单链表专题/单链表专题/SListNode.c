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
#include"SListNode.h"

void SListNodePrintf(SListNode* HeadPtr)
{
	SListNode* ptr = HeadPtr;
	while (ptr != NULL)
	{
		printf("%d->", ptr->data);
		ptr = ptr->NextPtr;
	}
	printf("NULL\n");
}

static SListNode* GetNode(SLNDataType x)
{
	SListNode* Ptr = (SListNode*)malloc(sizeof(SListNode));
	assert(Ptr);
	Ptr->data = x;
	Ptr->NextPtr = NULL;
	return Ptr;
}

void SListNodeEndPush(SListNode** HeadPPtr, SLNDataType x)
{
	assert(HeadPPtr);
	SListNode* NewNode = GetNode(x);
	NewNode->NextPtr = NULL;
	if (*HeadPPtr != NULL)
	{
		SListNode* EndPtr = *HeadPPtr;
		while (EndPtr->NextPtr != NULL)
		{
			EndPtr = EndPtr->NextPtr;
		}
		EndPtr->NextPtr = NewNode;
		NewNode = NULL;
	}
	else
	{
		*HeadPPtr = NewNode;
		NewNode = NULL;
	}
}

void SListNodeFrontPush(SListNode** HeadPPtr, SLNDataType x)
{
	assert(HeadPPtr);
	SListNode* NewNode = GetNode(x);
	NewNode->NextPtr = *HeadPPtr;
	*HeadPPtr = NewNode;
	NewNode = NULL;
}

void SListNodeEndPop(SListNode** HeadPPtr)
{
	assert(HeadPPtr);
	assert(*HeadPPtr);
	if ((*HeadPPtr)->NextPtr == NULL)
	{
		free(*HeadPPtr);
		*HeadPPtr = NULL;
	}
	else
	{
		SListNode* EndNodePtr = *HeadPPtr;
		SListNode* LastNodePtr = *HeadPPtr;
		while (EndNodePtr->NextPtr != NULL)
		{
			LastNodePtr = EndNodePtr;
			EndNodePtr = LastNodePtr->NextPtr;
		}
		free(EndNodePtr);
		EndNodePtr = NULL;
		LastNodePtr->NextPtr = NULL;
	}
}

void SListNodeFrontPop(SListNode** HeadPPtr)
{
	assert(HeadPPtr);
	assert(*HeadPPtr);
	SListNode* Ptr = *HeadPPtr;
	*HeadPPtr = (*HeadPPtr)->NextPtr;
	free(Ptr);
	Ptr = NULL;
}

SListNode* SListNodeFind(SListNode* HeadPtr, SLNDataType x)
{
	assert(HeadPtr);
	SListNode* Ptr = HeadPtr;
	while (Ptr != NULL)
	{
		if (Ptr->data == x)
		{
			return Ptr;
		}
		Ptr = Ptr->NextPtr;
	}
	return NULL;
}

void SListNodeInsertBefore(SListNode** Headpptr, SListNode* PosPtr, SLNDataType x)
{
	assert(Headpptr);
	assert(*Headpptr);
	assert(PosPtr);
	if (*Headpptr == PosPtr)
	{
		SListNodeFrontPush(Headpptr, x);
	}
	else
	{
		SListNode* LastPtr = *Headpptr;
		while (LastPtr->NextPtr != PosPtr)
		{
			LastPtr = LastPtr->NextPtr;
		}
		SListNode* NewNode = GetNode(x);
		NewNode->NextPtr = PosPtr;
		LastPtr->NextPtr = NewNode;
		NewNode = NULL;
	}
}

void SListNodeInsertAfter(SListNode* PosPtr, SLNDataType x)
{
	assert(PosPtr);
	SListNode* NewNode = GetNode(x);
	NewNode->NextPtr = PosPtr->NextPtr;
	PosPtr->NextPtr = NewNode;
	NewNode = NULL;
}