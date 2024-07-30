#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<vld.h>


//��˳����д洢�����������������������պ����
typedef int SLDataType;

//ʹ�ýṹ��ʵ��˳���
typedef struct SeqList
{
	SLDataType* p;
	int total;              //�����ɵ�������
	int valid;				//��Ч���ݸ���
}SeqList, * PSeqList;

//���һ���ѱ���ʼ����˳���ָ��
PSeqList SeqListGet(void);

//����˳���
void SeqListDestroy(PSeqList PSL);

//��ӡ˳���
void SeqListPrintf(const PSeqList ps);

//β��
void SeqListPushBack(PSeqList ps, SLDataType x);

//ͷ��
void SeqListPushFront(PSeqList ps, SLDataType x);

//βɾ
void SeqListPopBack(PSeqList ps);

//ͷɾ
void SeqListPopFront(PSeqList ps);

//��ָ��λ�ò���
void SeqListInsert(PSeqList ps, int pos, SLDataType x);

//ɾ��ָ��λ��
void SeqListErase(PSeqList ps, int pos);

//����Ŀ������
int SeqListFind(const PSeqList ps, int pos);

//��ָ��λ�ý����޸�
void SeqListModify(PSeqList ps, int pos, SLDataType x);