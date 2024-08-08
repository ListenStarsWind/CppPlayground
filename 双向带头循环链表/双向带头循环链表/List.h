#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"vld.h"

typedef int LTDataType;

typedef struct ListNode
{
	struct ListNode* prev;
	struct ListNode* next;
	LTDataType val;
}LT, * PLT;

PLT LTInit(void);

PLT BuyNode(LTDataType val);

void LTPushBack(const PLT head, LTDataType val);

//Can only be used when the type of "val" is int
void LTPrintf(const PLT head);

void LTDest(const PLT head);

void LTPushFront(const PLT head, LTDataType val);

void LTPopBack(const PLT head);

void LTPopFront(const PLT head);

PLT LTFind(PLT head, LTDataType val);

void LTInsertBefore(PLT pos, LTDataType val);

void LTErase(PLT pos);