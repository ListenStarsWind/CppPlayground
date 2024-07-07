#define _CRT_SECURE_NO_WARNINGS
/******************************************************************************************
* 【文件名称】：SList.h
* 【文件标识】：
* =========================================================================================
* 【当前作者】：听风若依
* 【当前版本】：1.0
* 【完成日期】：2024年 月日
* 【更新内容】：
* =========================================================================================
* 【历史作者】：听风若依
* 【历史版本】：V1.
* 【历史日期】：2024年 月日
* =========================================================================================
* 【开发平台】：VS2022
* 【程序功能】：
* =========================================================================================*/
#pragma once

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

//重命名单链表数值域中的数据类型
//Rename the data type in the value field of the singly linked list
typedef int SListDataType;

//定义单向链表的节点
//Define a Node in a Singly Linked List
typedef struct SListNode
{
	//数值域
	//Data Field
	SListDataType data;
	//指针域
	//Pointer Field
	struct SListNode* next;
}SListNode;

//创建节点并进行不完全初始化
//Create nodes and perform partial initialization
SListNode* CreateNode(SListDataType data);

//打印单链表中的全部元素
//Print all elements in the singly linked list
void SListPrintf(SListNode* PtrHead);

//在尾部插入新节点
//Insert a new node at the tail
void InsertTail(SListNode** PPtrHead, SListDataType x);

//在头部插入新节点
//Insert a new node at the head
void InsertHead(SListNode** PPtrHead, SListDataType x);

//删除尾部节点
//Delete the tail node
//如果没有节点可被删除，则返回EOF，否则返回0
//If there are no nodes to delete, return EOF; otherwise, return 0
int DelateTail(SListNode** PPtrHead);

//删除头部节点
//Delete the head node
//如果没有节点可被删除，则返回EOF，否则返回0
//If there are no nodes to delete, return EOF; otherwise, return 0
int DelateHead(SListNode** PPtrHead);

//查找节点
//Find node
//找到则返回该节点的指针，否则，返回空指针NULL
//If found, return a pointer to the node; otherwise, return a NULL pointer
SListNode* FindNode(SListNode* PtrHead, SListDataType x);

//在指定位置之前插入数据
//Insert data before the specified position
void InBefoPosi(SListNode** PPtrHead, SListNode* TargetPtr, SListDataType x);

//删除指定位置数据
//Delete data at the specified position
void DePosi(SListNode** PPtrHead, SListNode* TargetPtr);

//在指定位置之后插入数据
//Insert data after the specified position
void InAftPosi(SListNode* TargetPtr, SListDataType x);