#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct BinaryTreeNode BTNode, * pBTNode;

typedef pBTNode QDataType;
typedef struct QueueNode
{
	struct QueueNode* _next;
	QDataType _data;
}QNType, * PQNType;

typedef struct Quenu
{
	PQNType _phead;
	PQNType _ptail;
	int _size;
}QType, * PQType;

PQType QInit(void);

void QDestory(PQType pq);

void QPush(PQType pq, QDataType val);

int QSize(PQType pq);

void QPop(PQType pq);

QDataType QReadFront(PQType pq);

QDataType QReadBack(PQType pq);

bool IsEmptyQueue(PQType pq);