#include"Queue.h"

PQType QInit(void)
{
	PQType pq = (PQType)malloc(sizeof(QType));
	if (pq == NULL)
	{
		perror("QInit malloc fail");
		return NULL;
	}
	PQNType p = (PQNType)malloc(sizeof(QNType));
	if (p == NULL)
	{
		free(pq);
		perror("QInit SeqList head malloc fail");
		return NULL;
	}
	p->_next = NULL;
	pq->_phead = p;
	pq->_ptail = p;
	pq->_size = 0;
	return pq;
}

void QDestory(PQType pq)
{
	assert(pq);
	PQNType pCurrent = pq->_phead;
	PQNType pNext = NULL;
	while (pCurrent)
	{
		pNext = pCurrent->_next;
		free(pCurrent);
		pCurrent = pNext;
	}
	pq->_phead = NULL;
	pq->_ptail = NULL;
	pq->_size = 0;
	free(pq);
}

static PQNType BuyNode(QDataType val)
{
	PQNType p = (PQNType)malloc(sizeof(QNType));
	if (p == NULL)
	{
		perror("BuyNode malloc fail");
		return NULL;
	}
	p->_data = val;
	p->_next = NULL;
	return p;
}

void QPush(PQType pq, QDataType val)
{
	assert(pq);
	PQNType newNode = BuyNode(val);
	pq->_ptail->_next = newNode;
	pq->_ptail = newNode;
	pq->_size++;
}

int QSize(PQType pq)
{
	assert(pq);
	return pq->_size;
}

void QPop(PQType pq)
{
	assert(pq);
	if (QSize(pq) > 0)
	{
		if (pq->_phead->_next == pq->_ptail)
		{
			PQNType second = pq->_phead->_next->_next;
			free(pq->_phead->_next);
			pq->_phead->_next = second;
			pq->_size--;
			pq->_ptail = pq->_phead;
			return;
		}
		else
		{
			PQNType second = pq->_phead->_next->_next;
			free(pq->_phead->_next);
			pq->_phead->_next = second;
			pq->_size--;
			return;
		}
	}
	else
	{
		printf("The queue already null!\n");
		return;
	}
}

QDataType QReadFront(PQType pq)
{
	assert(pq);
	assert(QSize(pq) > 0); 
	return pq->_phead->_next->_data;
}

QDataType QReadBack(PQType pq)
{
	assert(pq);
	assert(QSize(pq) > 0);
	return pq->_ptail->_data;
}

bool IsEmptyQueue(PQType pq)
{
	if (QSize(pq) == 0)
		return true;
	else
		return false;
}