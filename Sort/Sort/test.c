#include"Sort.h"
#include<time.h>
#include<stdio.h>
#include<string.h>

pSortData BulidArray(int Size)
{
	pSortData pArray = (pSortData)malloc(sizeof(SortData)* Size);
	if (pArray == NULL)
	{
		perror("BulidArray malloc fail");
		return NULL;
	}
	int circuit = 0;
	for (; circuit < Size; circuit++)
	{
		pArray[circuit] = rand();
	}
	return pArray;
}

void pArrayPrintf(pSortData pArray, int Size)
{
	int circuit = 0;
	for (; circuit < Size; circuit++)
	{
		printf("%d ",pArray[circuit]);
	}
	printf("\n");
}

void test1()
{
	int Size = 10;
	pSortData pArray = BulidArray(Size);
	int circuit = 0;
	printf("The contents of the original array:\n");
	pArrayPrintf(pArray, Size);
	Shell_sort(pArray, Size);
	printf("\nThe contents of the sorted array:\n");
	pArrayPrintf(pArray, Size);
	free(pArray);
	pArray = NULL;
}

pSortData pArray_copy(pSortData pSource, int Size)
{
	pSortData pDestination = (pSortData)malloc(sizeof(SortData) * Size);
	if (pDestination == NULL)
	{
		perror("pArray_copy malloc fail");
		return NULL;
	}
	memcpy(pDestination, pSource, sizeof(SortData) * Size);
	return pDestination;
}

#define PerformanceTesting(NumSize, Proceedings)					 \
	void test_##Proceedings()										 \
	{																 \
		printf("The test begins.\n");								 \
		printf("The subroutine tested is " #Proceedings ".\n");		 \
		printf("The number of array members is " #NumSize ".\n");	 \
		srand((unsigned int)time(NULL));							 \
		int Size = NumSize;											 \
		pSortData pArray = BulidArray(Size);						 \
		int circuit = 0;											 \
		printf("\nThe contents of the original array:\n");			 \
		pArrayPrintf(pArray, Size);									 \
		clock_t begin = clock();									 \
		Proceedings(pArray, Size);									 \
		clock_t end = clock();										 \
		printf("\nThe contents of the sorted array:\n");			 \
		pArrayPrintf(pArray, Size);									 \
		free(pArray);												 \
		pArray = NULL;												 \
		printf("\nEnd of test.\n");									 \
		printf("The " #Proceedings " runtime is %dms.\n", end-begin);\
    }														

PerformanceTesting(100000, Quick_sort)

int main()
{	
	test_Quick_sort();
	return 0;
}