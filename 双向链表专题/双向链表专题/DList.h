#pragma once

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

//����˫�������д洢���ݵ�����
//Name the data type stored in the doubly linked list
typedef int DListDataType;

//����˫������ڵ�
//Define the doubly linked list node
typedef struct DListNode
{
	DListDataType data;
	struct DListNode* prev;
	struct DListNode* next;
}DListNode;

//˫�������ʼ��
//Initialize the doubly linked list
#define optimize//ʹ��ģ�����0��9ʱ��ע�͸�ָ��
#ifndef optimize
void InitDList(DListNode** HeadNode);
#else
DListNode* InitDList();
#endif

//˫������β��ڵ�
//Insert node at the tail of the doubly linked list
void InNodeTail(DListNode* phead, DListDataType x);

//˫�������ӡ
//Print doubly linked list
void PrintfDList(DListNode* phead);

//˫������ͷ��ڵ�
//Insert node at the head of the doubly linked list
void InNodeHead(DListNode* phead, DListDataType x);

//˫������βɾ�ڵ�
//Delete node from the tail of the doubly linked list
//�������EOF��˵�������ѿ�
//If EOF is returned, it indicates that the linked list is empty
//����0����˵����������
//Return 0 indicates that the operation was successful
int DeTail(DListNode* phead);

//˫������ͷɾ�ڵ�
//Delete node from the head of the doubly linked list
//�������EOF��˵�������ѿ�
//If EOF is returned, it indicates that the linked list is empty
//����0����˵����������
//Return 0 indicates that the operation was successful
int DeHead(DListNode* phead);

//����ָ���ڵ�
//Find the specified node
DListNode* FindNode(DListNode* phead, DListDataType x);

//��ָ��λ��֮�����
//Insert after the specified position
void InAfSpe(DListNode* pos, DListDataType x);

//��ָ��λ��֮ǰ����
//Insert before the specified position
void InBfSpe(DListNode* pos, DListDataType x);

//ɾ��ָ��λ�ýڵ�
//Delete the node at the specified position
void DePos(DListNode* pos);

//����˫������
//Destroy a doubly linked list
void DouList(DListNode* phead);