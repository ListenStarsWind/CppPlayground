#pragma once

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

//命名双向链表中存储数据的类型
//Name the data type stored in the doubly linked list
typedef int DListDataType;

//定义双向链表节点
//Define the doubly linked list node
typedef struct DListNode
{
	DListDataType data;
	struct DListNode* prev;
	struct DListNode* next;
}DListNode;

//双向链表初始化
//Initialize the doubly linked list
#define optimize//使用模块测试0到9时请注释该指令
#ifndef optimize
void InitDList(DListNode** HeadNode);
#else
DListNode* InitDList();
#endif

//双向链表尾插节点
//Insert node at the tail of the doubly linked list
void InNodeTail(DListNode* phead, DListDataType x);

//双向链表打印
//Print doubly linked list
void PrintfDList(DListNode* phead);

//双向链表头插节点
//Insert node at the head of the doubly linked list
void InNodeHead(DListNode* phead, DListDataType x);

//双向链表尾删节点
//Delete node from the tail of the doubly linked list
//如果返回EOF，说明链表已空
//If EOF is returned, it indicates that the linked list is empty
//返回0，则说明运行正常
//Return 0 indicates that the operation was successful
int DeTail(DListNode* phead);

//双向链表头删节点
//Delete node from the head of the doubly linked list
//如果返回EOF，说明链表已空
//If EOF is returned, it indicates that the linked list is empty
//返回0，则说明运行正常
//Return 0 indicates that the operation was successful
int DeHead(DListNode* phead);

//查找指定节点
//Find the specified node
DListNode* FindNode(DListNode* phead, DListDataType x);

//在指定位置之后插入
//Insert after the specified position
void InAfSpe(DListNode* pos, DListDataType x);

//在指定位置之前插入
//Insert before the specified position
void InBfSpe(DListNode* pos, DListDataType x);

//删除指定位置节点
//Delete the node at the specified position
void DePos(DListNode* pos);

//销毁双向链表
//Destroy a doubly linked list
void DouList(DListNode* phead);