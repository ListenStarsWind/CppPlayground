#pragma once

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

typedef int SinglyDataType;

typedef struct SinglyListNode
{
	SinglyDataType data;
	struct SinglyListNode* next;
}SinglyListNode,* PSinglyListNode;

//打印单链表
void SinglyListPrintf(PSinglyListNode PCurrent);

//头插
void SinglyListPushFront(PSinglyListNode* PPHead, SinglyDataType x);

//销毁单链表
void SinglyListDestroy(PSinglyListNode* PPDie);

//尾插
void SinglyListPushBack(PSinglyListNode* PPHead, SinglyDataType x);

//头删
void SinglyListPopFront(PSinglyListNode* PPHead);

//尾删
void SinglyListPopBack(PSinglyListNode* PPHead);