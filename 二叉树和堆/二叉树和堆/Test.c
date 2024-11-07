#include"Heap.h"
#include"time.h"

void test1()
{
	pHeap pH = HeapInit();
	int arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr)/sizeof(arr[0]);
	int current = 0;
	for(current = 0; current < sz; current++)
	{
		int i = arr[current];
		HeapPush(pH, i);
	}
	HeapDestroy(pH);
	pH = NULL;
}

void test2()
{
	pHeap pH = HeapInit();
	int arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int current = 0;
	for (current = 0; current < sz; current++)
	{
		int i = arr[current];
		HeapPush(pH, i);
	}
	HeapPop(pH);
	HeapDestroy(pH);
	pH = NULL;
}

void test3()
{
	pHeap pH = HeapInit();
	int arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int current = 0;
	for (current = 0; current < sz; current++)
	{
		int i = arr[current];
		HeapPush(pH, i);
	}
	while (!HeapEmpty(pH))
	{
		HeapData top = HeapTop(pH);
		printf("%d\n",top);
		HeapPop(pH);
	}
	HeapDestroy(pH);
	pH = NULL;
}

void test4()
{
	HeapData arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort1(arr, sz);
	int cir = 0;
	for (; cir < sz; cir++)
	{
		printf("arr[%d]=%d\n", cir, arr[cir]);
	}
}

void test5()
{
	HeapData arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort2(arr, sz);
	int cir = 0;
	for (; cir < sz; cir++)
	{
		printf("arr[%d]=%d\n", cir, arr[cir]);
	}
}

void test6()
{
	HeapData arr[] = { 65,100,70,32,50,60,85 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, sz);
	int cir = 0;
	for (; cir < sz; cir++)
	{
		printf("arr[%d]=%d\n", cir, arr[cir]);
	}
}

void CreateData(int k)
{
	FILE* pf = fopen("data.txt", "w");
	if (pf == NULL)
	{
		perror("CreateData open fail");
		return;
	}
	srand((unsigned int)time(NULL));
	while (k--)
	{
		int n = rand() % 10000;
		fprintf(pf, "%d\n", n);
	}
	fclose(pf);
	pf = NULL;
}

void test7()
{
	//CreateData(100000);
	int* pArray = TopK1(5);
	if (pArray != NULL)
	{
		int i = 0;
		for (; i < 5; i++)
		{
			printf("%d\n", pArray[i]);
		}
		free(pArray);
	}
}

void test8()
{
	//CreateData(100000);
	int* pArray = TopK(5);
	if (pArray != NULL)
	{
		int i = 0;
		for (; i < 5; i++)
		{
			printf("%d\n", pArray[i]);
		}
		free(pArray);
	}
}

int main()
{
	test4();
	return 0;
}