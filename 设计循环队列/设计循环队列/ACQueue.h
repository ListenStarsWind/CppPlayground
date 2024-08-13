
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

typedef int CQData;

typedef struct {
	CQData* _pArray;
	int _Front;
	int _Rear;
	int _Capacity;
	int _Size;
} MyCircularQueue;

typedef MyCircularQueue* PMyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k);

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value);

bool myCircularQueueDeQueue(MyCircularQueue* obj);

int myCircularQueueFront(MyCircularQueue* obj);

int myCircularQueueRear(MyCircularQueue* obj);

bool myCircularQueueIsEmpty(MyCircularQueue* obj);

bool myCircularQueueIsFull(MyCircularQueue* obj);

void myCircularQueueFree(MyCircularQueue* obj);

