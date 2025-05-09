#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：SeqList.h
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

#define __DEBUG__//打开进入测试模块,关闭进入主体模块

#include<stdio.h>//第一次使用于SL初始化函数（位于sequential_list.c）NULL
#include<stdlib.h>//第一次用于宏ASSERT中exit函数
#include<string.h>//第一次用于函数strrchr，见宏__M_FILE__
#include"vld.h"

#define SLINIT__TEST  //定义所在分支正确
#define SLPUSHBACK  //定义所在分支正确
 //#define __POP__ //定义所在分支健壮性不足


  //空指针判断
#define __M_FILE__ (strrchr(__FILE__,'\\') ? strrchr(__FILE__,'\\')+1 : __FILE__)

#include <stdio.h>
#define ASSERT(p) if(p == NULL)\
		{\
		printf("The address " #p " is null." "\n");\
		printf("%s\n",__M_FILE__);\
		printf("%d\n",__LINE__);\
		exit(EOF);\
		}

//动态调整
#define Realloc(p,type,n) (type*)realloc(p, n * sizeof(type))

 //记得加分号
typedef int SLDataType;

//我的动态顺序表
typedef struct SeqList
{
	SLDataType* arr; //SLDataType的第一次使用
	//size记录有效数据个数
	int size;
	//capacity记录内存块大小
	int capacity;
}SL;

//SL初始化
#ifdef SLINIT__TEST

void SLInit(SL* ps);

#else

void SLInit(SL ps);

#endif

//SL销毁
void SLDestroy(SL* ps);

//尾插函数
#ifdef SLPUSHBACK
void SLPushBack(SL* ps, SLDataType x); //SLDataType的第二次使用
#else

#endif

//头插函数
void SLPushFront(SL* ps, SLDataType x);


void SLPopBack(SL* ps);

//头删函数
void SLPopFront(SL* ps);

