#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  月日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：
 *******************************************************************************************/
#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int SLNDataType;

//Singly：单一的，表示每个节点只有一个指向下一个节点的链接。
//单链表 
//Singly Linked List
typedef struct SListNode
{
	//数值域
	SLNDataType data;
	//指针域
	struct SListNode* NextPtr;
}SListNode;

//打印单链表
void SListNodePrintf(SListNode* HeadPtr);

//尾插
void SListNodeEndPush(SListNode** HeadPPtr, SLNDataType x);

//头插
void SListNodeFrontPush(SListNode** HeadPPtr, SLNDataType x);

//尾删
void SListNodeEndPop(SListNode** HeadPPtr);

//头删
void SListNodeFrontPop(SListNode** HeadPPtr);

//查找
SListNode* SListNodeFind(SListNode* HeadPtr, SLNDataType x);

//insert data before a specified position
void SListNodeInsertBefore(SListNode** Headpptr, SListNode* PosPtr, SLNDataType x);

//insert data before a specified position
void SListNodeInsertAfter(SListNode* PosPtr, SLNDataType x);