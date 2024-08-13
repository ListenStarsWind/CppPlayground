//Circular Queue By Unheadered Singly Circular Linked List
#include"LCQueue.h"


static PListNode BuyNode()
{
	PListNode p = (PListNode)malloc(sizeof(ListNode));
	if (p == NULL)
	{
		perror("BuyNode fail");
		return NULL;
	}
	return p;
}

MyCircularQueue* myCircularQueueCreate(int k) {
	PMyCircularQueue p = (PMyCircularQueue)malloc(sizeof(MyCircularQueue));
	if (p == NULL)
	{
		perror("myCircularQueueCreate fail");
		return NULL;
	}
	p->_Capacity = k;
	p->_Size = 0;

	PListNode pn = BuyNode();
	PListNode pTail = pn;
	p->_pFront = pn;
	p->_pRear = pn;
	while (k--)
	{
		pn = BuyNode();
		pTail->_next = pn;
		pTail = pTail->_next;
	}
	pTail->_next = p->_pFront;
	return p;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	assert(obj);
	if (myCircularQueueIsFull(obj))
	{
		return false;
	}
	else
	{
		obj->_pRear->_val = value;
		obj->_pRear = obj->_pRear->_next;
		obj->_Size++;
		return true;
	}
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return false;
	}
	else
	{
		obj->_pFront = obj->_pFront->_next;
		obj->_Size--;
		return true;
	}
}

int myCircularQueueFront(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	else
	{
		return obj->_pFront->_val;
	}
}

int myCircularQueueRear(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	else
	{
		PListNode pTail = obj->_pFront;
	while (pTail->_next != obj->_pRear)
	{
		pTail = pTail->_next;
	}
	return pTail->_val;
	}
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	assert(obj);
	return obj->_pRear == obj->_pFront;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
	assert(obj);
	return obj->_pRear->_next == obj->_pFront;
}

void ListDestory(PListNode pList)
{
	assert(pList);
	PListNode pHead = pList;
	PListNode pNext = NULL;
	do
	{
		pNext = pList->_next;
		free(pList);
		pList = pNext;
	} while (pList != pHead);
}

void myCircularQueueFree(MyCircularQueue* obj) {
	assert(obj);
	ListDestory(obj->_pFront);
	free(obj);
}
