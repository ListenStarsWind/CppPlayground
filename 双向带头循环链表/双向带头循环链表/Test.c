#include"List.h"

//Used test "LTPushBack"
void Test1()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 1);
	LTPushBack(head, 2);
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}

//Used test "LTPushFront"
void Test2()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}

//Used test "LTPopBack"
void Test3()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	LTPopBack(head);
	LTPopBack(head);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}

//Used test "LTPopFront"
void Test4()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	LTPopBack(head);
	LTPopBack(head);
	LTPrintf(head);
	LTPopFront(head);
	LTPopFront(head);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}

//Used test "LTInsertBefore"
void Test5()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPrintf(head);
	PLT find = LTFind(head, 2);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTInsertBefore(find, 1);
	}
	LTPrintf(head);
	find = LTFind(head, 5);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTInsertBefore(find, 4);
	}
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}

//Used test "LTErase"
void Test6()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	PLT find = LTFind(head, 2);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTErase(find);
	}
	LTPrintf(head);
	find = LTFind(head, 3);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTErase(find);
	}
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}

int main()
{
	Test4();
	return 0;
}