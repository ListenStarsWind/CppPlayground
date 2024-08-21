#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<stdio.h>
#include"vld.h"

typedef int HeapData, * pHeapData;
typedef struct Heap
{
	pHeapData _pArray;
	int _Capacity;
	int _Size;
}Heap, * pHeap;

bool rule(HeapData child, HeapData parent);

pHeap HeapInit(void);

void HeapDestroy(pHeap pH);

void adjustUP(HeapData* pArray, int Size, int Child);

void HeapPush(pHeap pH, HeapData val);

int HeapSize(pHeap pH);

bool HeapEmpty(pHeap pH);

void adjustDOWN(HeapData* pArray, int Size, int Parent);

void HeapPop(pHeap pH);

HeapData HeapTop(pHeap pH);

void HeapSort1(pHeapData pArray, int Size);

void HeapSort2(pHeapData pArray, int Size);

void HeapSort(pHeapData pArray, int Size);