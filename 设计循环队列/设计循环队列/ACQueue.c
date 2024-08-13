#include"ACQueue.h"

//Circular Queue By Array

MyCircularQueue* myCircularQueueCreate(int k)
{
	PMyCircularQueue p = (PMyCircularQueue)malloc(sizeof(MyCircularQueue));
	if (p == NULL)
	{
		perror("myCircularQueueCreate malloc fail");
		return NULL;
	}

	CQData* arr = (CQData*)malloc(sizeof(CQData)*(k+1));
	if (arr == NULL)
	{
		printf("Warning: Memory Leak.\n");
		perror("Array malloc fail");
		return NULL;
	}

	p->_pArray = arr;
	p->_Front = 0;
	p->_Rear = 0;
	p->_Size = 0;
	p->_Capacity = k;
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
		obj->_pArray[obj->_Rear] = value;
		obj->_Rear = (obj->_Rear + 1) % (obj->_Capacity + 1);
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
		obj->_Front = (obj->_Front + 1) % (obj->_Capacity + 1);
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
	return obj->_pArray[obj->_Front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	return obj->_pArray[(obj->_Rear + obj->_Capacity) % (obj->_Capacity + 1)];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	assert(obj);
	return obj->_Front == obj->_Rear;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
	assert(obj);
	return ((obj->_Rear + 1) % (obj->_Capacity + 1)) == obj->_Front;
}

void myCircularQueueFree(MyCircularQueue* obj) {
	assert(obj);
	free(obj->_pArray);
	free(obj);
}