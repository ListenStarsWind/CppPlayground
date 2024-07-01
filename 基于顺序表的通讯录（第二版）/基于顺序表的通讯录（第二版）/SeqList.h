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

#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include"vld.h"

//打开进入顺序表测试模块，关闭进入通讯录测试模块
//Open and Enter Sequence List Test Module, Close and Enter Address Book Test Module
#define TEST_SEQLIST

//内存块中的待选数据类型
//The candidate data types in the memory block
typedef int typedata;

//顺序表的定义
//Definition of a Sequential List
typedef struct SeqList
{
	//用于维护数据的指针
	//Pointer for Maintaining Data
	typedata* ptr;

	//描述内存块大小
	//Describe Memory Block Size
	int capacity;

	//描述有效数据个数
	//Describe Number of Valid Data Items
	int datacount;
}SeqList;

//顺序表的初始化
//Initialization of a Sequential List
void SeqListInit(SeqList* seqListPtr);

//顺序表的销毁
//Destruction of a Sequential List
void SeqListDestroy(SeqList* seqListPtr);

//顺序表的指定位置插入
//Insertion at a Specific Position in a Sequential List
void SeqListInsertAtPosition(SeqList* seqListPtr, int Position, typedata x);

//顺序表的指定位置删除
//Deletion at a Specific Position in a Sequential List
void SeqListDeleteAtPosition(SeqList* seqListPtr, int Position);

//顺序表的开头插入
//Insertion at the Beginning of a Sequential List
void SeqListInsertAtBeginning(SeqList* seqListPtr, typedata x);

//顺序表的尾部插入
//Insertion at the End of a Sequential List
void SeqListInsertAtEnd(SeqList* seqListPtr, typedata x);

//顺序表的开头删除
//Deletion at the Beginning of a Sequential List
void SeqListDeleteAtBeginning(SeqList* seqListPtr);

//顺序表的尾部删除
//Deletion at the End of a Sequential List
void SeqListDeleteAtEnd(SeqList* seqListPtr);

//顺序表的查找
//Search in a Sequential List
int SeqListSearch(SeqList* seqListPtr, typedata x);

//顺序表的展示
//Display of a Sequential List
void SeqListDisplay(SeqList* seqListPtr);