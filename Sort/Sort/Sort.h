#pragma once

#include<stdbool.h>
#include<stdlib.h>
#include<string.h>


typedef int SortData, * pSortData;

bool compare(SortData val1, SortData val2);

void Swap(pSortData p1, pSortData p2);

void Bubble_sort(pSortData pArray, int Size);

void Insert_sort(pSortData pArray, int Size);

void Shell_sort(pSortData pArray, int Size);

void Select_sort(pSortData pArray, int Size);

void Heap_sort(pSortData pArray, int Size);

void Quick_sort(pSortData pArray, int Size);

int middle_of_three(pSortData pArray, int left, int right);

void Quick_sort_NonR(pSortData pArray, int Size);

void Merge_sort(pSortData pArray, int Size);

void Merge_sort_NonR(pSortData pArray, int Size);

void Merge_sort_NonR1(pSortData pArray, int Size);