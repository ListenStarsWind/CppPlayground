#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

typedef int CQData;

typedef struct ListNode
{
	CQData _val;
	struct ListNode* _next;
}ListNode, * PListNode;

typedef struct {
	PListNode _pFront;
	PListNode _pRear;
	int _Capacity;
	int _Size;
} MyCircularQueue;

typedef MyCircularQueue* PMyCircularQueue;

//The parameter "k" is used to describe the maximum number of elements that the queue can hold.
MyCircularQueue* myCircularQueueCreate(int k);

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value);

bool myCircularQueueDeQueue(MyCircularQueue* obj);

int myCircularQueueFront(MyCircularQueue* obj);

int myCircularQueueRear(MyCircularQueue* obj);

bool myCircularQueueIsEmpty(MyCircularQueue* obj);

bool myCircularQueueIsFull(MyCircularQueue* obj);

void myCircularQueueFree(MyCircularQueue* obj);

