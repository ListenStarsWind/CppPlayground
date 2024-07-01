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
#include"SeqList.h"

//前置声明
//Forward declaration
void SeqListInsertAtPosition(SeqList* seqListPtr, int Position, typeint x);


void SeqListInit(SeqList* seqListPtr)
{
	assert(seqListPtr);
	seqListPtr->ptr = NULL;
	seqListPtr->capacity = seqListPtr->datacount = 0;

	//历史数据初始化
	//Historical data initialization
	FILE* p = NULL;
	p = fopen("data.txt", "rb");
	if (p == NULL)
	{
		;
	}
	else
	{
		typeint i;
		while (fread(&i, sizeof(typeint), 1, p))
		{
			SeqListInsertAtPosition(seqListPtr, seqListPtr->datacount, i);
		}
		if (feof(p))
		{
			//历史数据读取成功
			printf("Historical data read successfully\n");
		}
		else
		{
			//历史数据读取错误
			perror("Historical data read error");
			exit(-1);
		}
		fclose(p);
		p = NULL;
	}
}

void SeqListDestroy(SeqList* seqListPtr)
{
	assert(seqListPtr);

	//数据储存
	//Data storage
	FILE* p = NULL;
	p = fopen("data.txt", "wb");
	if (p == NULL)
	{
		//数据存储失败
		perror("Data storage failed");

		//数据应急保护
		//Data emergency protection
		while (1);
	}
	else
	{
		size_t count = 0;
		count = fwrite(seqListPtr->ptr, sizeof(typeint), seqListPtr->datacount, p);
		if (count != seqListPtr->datacount)
		{
			//数据存储失败
			perror("Data storage failed");

			//数据应急保护
			//Data emergency protection
			while (1);
		}
		fclose(p);
		p = NULL;
	}
	free(seqListPtr->ptr);
	seqListPtr->ptr = NULL;
	seqListPtr->capacity = seqListPtr->datacount = 0;
}

//内存块大小调整宏
//Memory Block Size Adjustment Macro
#define Realloc(type, ptr,count) ((type*)realloc(ptr,count*sizeof(type)))

//内存块扩展
//Memory Block Expansion
static void MemoryBlockExpand(SeqList* seqListPtr)
{
	//用于描述新的内存块大小
	//Used to Describe the Size of the New Memory Block
	int newcapacity = seqListPtr->capacity == 0 ? 4 : seqListPtr->capacity * 2;

	//防止新内存块开辟失败，创建第三方指针存储
	//Prevent Failure in Allocating New Memory Block, Create Third-Party Pointer Storage
	typeint* p = Realloc(typeint, seqListPtr->ptr, newcapacity);
	assert(p);
	seqListPtr->ptr = p;
	seqListPtr->capacity = newcapacity;
}

//这两个内存块调整函数不直接调用，所以不进行断言
//These two memory block adjustment functions are not directly called, so no assertion is made

//内存块缩小
//Memory Block Reduction
static void MemoryBlockShrink(SeqList* seqListPtr)
{
	//用于描述新的内存块大小
	//Used to Describe the Size of the New Memory Block
	int newcapacity = seqListPtr->datacount == 0 ? 4 : seqListPtr->datacount;

	//防止新内存块开辟失败，创建第三方指针存储
	//Prevent Failure in Allocating New Memory Block, Create Third-Party Pointer Storage
	typeint* p = Realloc(typeint, seqListPtr->ptr, newcapacity);
	assert(p);
	seqListPtr->ptr = p;
	seqListPtr->capacity = newcapacity;
}

void SeqListInsertAtPosition(SeqList* seqListPtr, int Position, typeint x)
{
	assert(seqListPtr);

	//判断是否有足够空间插入
	//Check if There is Enough Space for Insertion
	if (seqListPtr->capacity == seqListPtr->datacount)
	{
		MemoryBlockExpand(seqListPtr);
	}

	//判断插入位置是否非法
	//Check if the Insertion Position is Invalid
	if (Position >= 0 && Position <= seqListPtr->datacount)
	{
		int i = 0;
		for (i = seqListPtr->datacount; i > Position; i--)
		{
			seqListPtr->ptr[i] = seqListPtr->ptr[i - 1];
		}
		seqListPtr->ptr[Position] = x;
		seqListPtr->datacount++;
	}
	else
	{
		//插入失败：位置非法！
		printf("Insertion Failed: Invalid Position!\n");
	}
}

void SeqListDeleteAtPosition(SeqList* seqListPtr, int Position)
{
	assert(seqListPtr);

	//判断是否还有数据可以被删除
	//Deletion Failed: Check if There is Any Data Left to Delete
	if (seqListPtr->datacount == 0)
	{
		//删除失败：这个内存块中已经没有有效数据了！
		printf("Deletion Failed: No Valid Data in This Memory Block!\n");
	}
	else
	{
		//判断删除位置是否非法
		//Check if the Deletion Position is Invalid
		if (Position >= 0 && Position < seqListPtr->datacount)
		{
			int i = 0;
			for (i = Position; i < seqListPtr->datacount - 1; i++)
			{
				seqListPtr->ptr[i] = seqListPtr->ptr[i + 1];
			}
			seqListPtr->datacount--;
		}
		else
		{
			//删除失败：位置非法！
			printf("Deletion Failed: Invalid Position!\n");
		}
	}
	if (seqListPtr->datacount * 2 < seqListPtr->capacity)
	{
		MemoryBlockShrink(seqListPtr);
	}
}

void SeqListInsertAtBeginning(SeqList* seqListPtr, typeint x)
{
	assert(seqListPtr);

	//判断是否有足够空间插入
	//Check if There is Enough Space for Insertion
	if (seqListPtr->capacity == seqListPtr->datacount)
	{
		MemoryBlockExpand(seqListPtr);
	}

	int i = 0;
	for (i = seqListPtr->datacount; i > 0; i--)
	{
		seqListPtr->ptr[i] = seqListPtr->ptr[i - 1];
	}
	seqListPtr->ptr[0] = x;
	seqListPtr->datacount++;
}

void SeqListInsertAtEnd(SeqList* seqListPtr, typeint x)
{
	assert(seqListPtr);

	//判断是否有足够空间插入
	//Check if There is Enough Space for Insertion
	if (seqListPtr->capacity == seqListPtr->datacount)
	{
		MemoryBlockExpand(seqListPtr);
	}

	seqListPtr->ptr[seqListPtr->datacount] = x;
	seqListPtr->datacount++;
}

void SeqListDeleteAtBeginning(SeqList* seqListPtr)
{
	assert(seqListPtr);

	//判断是否还有数据可以被删除
	//Deletion Failed: Check if There is Any Data Left to Delete
	if (seqListPtr->datacount == 0)
	{
		//这个内存块中已经没有有效数据了！
		printf("There is no valid data in this memory block anymore!\n");
	}
	else
	{
		int i = 0;
		for (i = 0; i < seqListPtr->datacount - 1; i++)
		{
			seqListPtr->ptr[i] = seqListPtr->ptr[i + 1];
		}
		seqListPtr->datacount--;
	}
	if (seqListPtr->datacount * 2 < seqListPtr->capacity)
	{
		MemoryBlockShrink(seqListPtr);
	}
}

void SeqListDeleteAtEnd(SeqList* seqListPtr)
{
	assert(seqListPtr);

	//判断是否还有数据可以被删除
	//Deletion Failed: Check if There is Any Data Left to Delete
	if (seqListPtr->datacount == 0)
	{
		//这个内存块中已经没有有效数据了！
		printf("There is no valid data in this memory block anymore!\n");
	}
	else
	{
		seqListPtr->datacount--;
	}
	if (seqListPtr->datacount * 2 < seqListPtr->capacity)
	{
		MemoryBlockShrink(seqListPtr);
	}
}

int SeqListSearch(SeqList* seqListPtr, typeint x)
{
	assert(seqListPtr);
	int i = 0;
	for (i = 0; i < seqListPtr->datacount; i++)
	{
		if (seqListPtr->ptr[i] == x)
		{
			return i;
		}
	}
	return -1;
}

void SeqListDisplay(SeqList* seqListPtr)
{
	assert(seqListPtr);
	int i = 0;
	for (i = 0; i < seqListPtr->datacount; i++)
	{
		printf("%d ", seqListPtr->ptr[i]);
	}
	printf("\n");
}