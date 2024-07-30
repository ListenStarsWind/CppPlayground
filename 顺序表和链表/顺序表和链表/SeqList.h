#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<vld.h>


//将顺序表中存储的数据类型重命名，便于日后管理
typedef int SLDataType;

//使用结构体实现顺序表
typedef struct SeqList
{
	SLDataType* p;
	int total;              //可容纳的最大个数
	int valid;				//有效数据个数
}SeqList, * PSeqList;

//获得一个已被初始化的顺序表指针
PSeqList SeqListGet(void);

//销毁顺序表
void SeqListDestroy(PSeqList PSL);

//打印顺序表
void SeqListPrintf(const PSeqList ps);

//尾插
void SeqListPushBack(PSeqList ps, SLDataType x);

//头插
void SeqListPushFront(PSeqList ps, SLDataType x);

//尾删
void SeqListPopBack(PSeqList ps);

//头删
void SeqListPopFront(PSeqList ps);

//在指定位置插入
void SeqListInsert(PSeqList ps, int pos, SLDataType x);

//删除指定位置
void SeqListErase(PSeqList ps, int pos);

//查找目标数据
int SeqListFind(const PSeqList ps, int pos);

//对指定位置进行修改
void SeqListModify(PSeqList ps, int pos, SLDataType x);