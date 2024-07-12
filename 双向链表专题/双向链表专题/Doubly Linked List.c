#define _CRT_SECURE_NO_WARNINGS
#include"DList.h"

//创建并初始化节点
//Create and initialize a node
static DListNode* CreaNode(DListDataType x)
{
	DListNode* NewNode = (DListNode*)malloc(sizeof(DListNode));
	if (NewNode == NULL)
	{
		perror("Node creation failed:");
		exit(1);
	}
	NewNode->data = x;
	NewNode->prev = NewNode->next = NewNode;
	return NewNode;
}

#ifndef optimize

void InitDList(DListNode** HeadNode)
{
	//头结点中的数据是无效的，可以传满足参数类型的任意值
	//The data in the head node is invalid; any value that satisfies the parameter type can be passed
	*HeadNode = CreaNode(-1);
}

#else

DListNode* InitDList()
{
	DListNode* phead = CreaNode(-1);
	return phead;
}

#endif

void InNodeTail(DListNode* phead, DListDataType x)
{
	assert(phead);
	DListNode* newnode = CreaNode(x);
	newnode->next = phead;
	newnode->prev = phead->prev;
	phead->prev->next = newnode;
	phead->prev = newnode;
}

void PrintfDList(DListNode* phead)
{
	DListNode* ptemp = phead->next;
	while (ptemp != phead)
	{
		printf("%d->", ptemp->data);
		ptemp = ptemp->next;
	}
	printf("stop\n");
}

void InNodeHead(DListNode* phead, DListDataType x)
{
	assert(phead);
	DListNode* newnode = CreaNode(x);
	newnode->prev = phead;
	newnode->next = phead->next;
	phead->next->prev = newnode;
	phead->next = newnode;
}

int DeTail(DListNode* phead)
{
	assert(phead);
	if (phead->next == phead)
	{
		//这个链表已经空了
		return EOF;
	}
	else
	{
		DListNode* ptemp = phead->prev;
		phead->prev = ptemp->prev;
		ptemp->prev->next = phead;
		free(ptemp);
		ptemp = NULL;
		return 0;
	}
}

int DeHead(DListNode* phead)
{
	assert(phead);
	if (phead->next == phead)
	{
		//这个链表已经空了
		return EOF;
	}
	else
	{
		DListNode* ptemp = phead->next;
		phead->next = ptemp->next;
		ptemp->next->prev = phead;
		free(ptemp);
		ptemp = NULL;
		return 0;
	}
}

DListNode* FindNode(DListNode* phead, DListDataType x)
{
	assert(phead);
	DListNode* traversal = phead->next;
	while (traversal != phead)
	{
		if (traversal->data == x)
		{
			return traversal;
		}
		traversal = traversal->next;
	}
	return NULL;
}

void InAfSpe(DListNode* pos, DListDataType x)
{
	assert(pos);
	DListNode* new = CreaNode(x);
	new->next = pos->next;
	new->prev = pos;
	pos->next = new;
	new->next->prev = new;
}

void InBfSpe(DListNode* pos, DListDataType x)
{
	assert(pos);
	DListNode* new = CreaNode(x);
	new->next = pos;
	new->prev = pos->prev;
	pos->prev = new;
	new->prev->next = new;
}

void DePos(DListNode* pos)
{
	assert(pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
	pos = NULL;
}

void DouList(DListNode* phead)
{
	assert(phead);
	DListNode* ptemp = phead->next;
	DListNode* next = NULL;
	while (ptemp != phead)
	{
		next = ptemp->next;
		free(ptemp);
		ptemp = next;
	}
	free(phead);
	phead = NULL;
}