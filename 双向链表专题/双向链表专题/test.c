#define _CRT_SECURE_NO_WARNINGS
#include"DList.h"

//Ä£¿é²âÊÔ1£ºInitDList
void test1()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
}

//Ä£¿é²âÊÔ2£ºInNodeTail
void test2()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeTail(HeadNode, 1);
	InNodeTail(HeadNode, 2);
	InNodeTail(HeadNode, 3);
	PrintfDList(HeadNode);
}

//Ä£¿é²âÊÔ3£ºInNodeHead
void test3()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	PrintfDList(HeadNode);
}

//Ä£¿é²âÊÔ4£ºDeTail
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

//Ä£¿é²âÊÔ4£ºDeHead
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

//Ä£¿é²âÊÔ6£ºFindNode
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

//Ä£¿é²âÊÔ7£ºInAfSpe
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

//Ä£¿é²âÊÔ8£ºInBfSpe
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

//Ä£¿é²âÊÔ9£ºDePos
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

//Ä£¿é²âÊÔ10£ºDListNode* InitDList()
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

//Ä£¿é²âÊÔ11£ºDouList
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