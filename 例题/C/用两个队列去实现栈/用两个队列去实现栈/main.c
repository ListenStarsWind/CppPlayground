#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<stdbool.h>
#include"vld.h"

typedef int QDataType;
typedef struct QueueNode {
    struct QueueNode* _next;
    QDataType _data;
} QNType, * PQNType;

typedef struct Quenu {
    PQNType _phead;
    PQNType _ptail;
    int _size;
} QType, * PQType;

PQType QInit(void) {
    PQType pq = (PQType)malloc(sizeof(QType));
    if (pq == NULL) {
        perror("QInit malloc fail");
        return NULL;
    }
    PQNType p = (PQNType)malloc(sizeof(QNType));
    if (p == NULL) {
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

void QDestory(PQType pq) {
    assert(pq);
    PQNType pCurrent = pq->_phead;
    PQNType pNext = NULL;
    while (pCurrent) {
        pNext = pCurrent->_next;
        free(pCurrent);
        pCurrent = pNext;
    }
    pq->_phead = NULL;
    pq->_ptail = NULL;
    pq->_size = 0;
    free(pq);
}

static PQNType BuyNode(QDataType val) {
    PQNType p = (PQNType)malloc(sizeof(QNType));
    if (p == NULL) {
        perror("BuyNode malloc fail");
        return NULL;
    }
    p->_data = val;
    p->_next = NULL;
    return p;
}

void QPush(PQType pq, QDataType val) {
    assert(pq);
    PQNType newNode = BuyNode(val);
    pq->_ptail->_next = newNode;
    pq->_ptail = newNode;
    pq->_size++;
}

int QSize(PQType pq) {
    assert(pq);
    return pq->_size;
}

void QPop(PQType pq) {
    assert(pq);
    if (QSize(pq) > 0) {
        if (pq->_phead->_next == pq->_ptail) {
            PQNType second = pq->_phead->_next->_next;
            free(pq->_phead->_next);
            pq->_phead->_next = second;
            pq->_size--;
            pq->_ptail = pq->_phead;
            return;
        }
        else {
            PQNType second = pq->_phead->_next->_next;
            free(pq->_phead->_next);
            pq->_phead->_next = second;
            pq->_size--;
            return;
        }
    }
    else {
        printf("The queue already null!\n");
        return;
    }
}

QDataType QReadFront(PQType pq) {
    assert(pq);
    assert(QSize(pq) > 0);
    return pq->_phead->_next->_data;
}

QDataType QReadBack(PQType pq) {
    assert(pq);
    assert(QSize(pq) > 0);
    return pq->_ptail->_data;
}

typedef struct {
    PQType _p1;
    PQType _p2;
} MyStack;

MyStack* myStackCreate() {
    MyStack* p = (MyStack*)malloc(sizeof(MyStack));
    if (p == NULL) {
        perror("myStackCreate malloc fail");
        return NULL;
    }
    p->_p1 = QInit();
    p->_p2 = QInit();
    return p;
}

void myStackPush(MyStack* obj, int x) {
    PQType Empty = obj->_p1;
    PQType Have = obj->_p2;
    if (QSize(obj->_p1) != 0) {
        Empty = obj->_p2;
        Have = obj->_p1;
    }
    QPush(Have, x);
}

QDataType QPopFront(PQType pq) {
    QDataType ret = QReadFront(pq);
    QPop(pq);
    return ret;
}

int myStackPop(MyStack* obj) {
    QDataType prov = 0;
    PQType Empty = obj->_p1;
    PQType Have = obj->_p2;
    if (QSize(obj->_p1) != 0) {
        Empty = obj->_p2;
        Have = obj->_p1;
    }
    while (QSize(Have) > 1) {
        prov = QPopFront(Have);
        QPush(Empty, prov);
    }
    prov = QPopFront(Have);
    return prov;
}

int myStackTop(MyStack* obj) {
    PQType Empty = obj->_p1;
    PQType Have = obj->_p2;
    if (QSize(obj->_p1) != 0) {
        Empty = obj->_p2;
        Have = obj->_p1;
    }
    return QReadBack(Have);
}

bool myStackEmpty(MyStack* obj) {
    if (QSize(obj->_p1) == 0 && QSize(obj->_p2) == 0) {
        return true;
    }
    else {
        return false;
    }
}

void myStackFree(MyStack* obj) {
    QDestory(obj->_p1);
    QDestory(obj->_p2);
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/


int main()
{
    MyStack* p = myStackCreate();
    myStackPush(p, 1);
    myStackPush(p, 2);
    printf("%d\n", myStackTop(p));
    printf("%d\n", myStackPop(p));
    printf("%d\n", myStackEmpty(p));
    myStackFree(p);
    p = NULL;
}
