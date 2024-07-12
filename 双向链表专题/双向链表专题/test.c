#define _CRT_SECURE_NO_WARNINGS
#include"DList.h"

//ģ�����1��InitDList
void test1()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
}

//ģ�����2��InNodeTail
void test2()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeTail(HeadNode, 1);
	InNodeTail(HeadNode, 2);
	InNodeTail(HeadNode, 3);
	PrintfDList(HeadNode);
}

//ģ�����3��InNodeHead
void test3()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	PrintfDList(HeadNode);
}

//ģ�����4��DeTail
void test4()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	while (DeTail(HeadNode) != EOF)
	{
		;
	}
	PrintfDList(HeadNode);
}

//ģ�����4��DeHead
void test5()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DeHead(HeadNode);
	PrintfDList(HeadNode);
	DeHead(HeadNode);
	PrintfDList(HeadNode);
	DeHead(HeadNode);
	PrintfDList(HeadNode);
	while (DeHead(HeadNode) != EOF)
	{
		;
	}
	PrintfDList(HeadNode);
}

//ģ�����6��FindNode
void test6()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 4);
	PrintfDList(pfind);
}

//ģ�����7��InAfSpe
void test7()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 1);
	InAfSpe(pfind, 2);
	PrintfDList(HeadNode);
	pfind = FindNode(HeadNode, 4);
	InAfSpe(pfind, 5);
	PrintfDList(HeadNode);
}

//ģ�����8��InBfSpe
void test8()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 3);
	InBfSpe(pfind, 2);
	PrintfDList(HeadNode);
	pfind = FindNode(HeadNode, 6);
	InBfSpe(pfind, 5);
	PrintfDList(HeadNode);
}

//ģ�����9��DePos
void test9()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 4);
	DePos(pfind);
	PrintfDList(HeadNode);
}

//ģ�����10��DListNode* InitDList()
void test10()
{
	DListNode* HeadNode = NULL;
	HeadNode = InitDList();
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	while (DeTail(HeadNode) != EOF)
	{
		;
	}
	PrintfDList(HeadNode);
}

//ģ�����11��DouList
void test11()
{
	DListNode* HeadNode = NULL;
	HeadNode = InitDList();
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DouList(HeadNode);
	HeadNode = NULL;
}

int main()
{
	test11();
	return 0;
}