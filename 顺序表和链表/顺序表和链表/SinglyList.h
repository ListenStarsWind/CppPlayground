#pragma once

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

typedef int SinglyDataType;

typedef struct SinglyListNode
{
	SinglyDataType data;
	struct SinglyListNode* next;
}SinglyListNode,* PSinglyListNode;

//��ӡ������
void SinglyListPrintf(PSinglyListNode PCurrent);

//ͷ��
void SinglyListPushFront(PSinglyListNode* PPHead, SinglyDataType x);

//���ٵ�����
void SinglyListDestroy(PSinglyListNode* PPDie);

//β��
void SinglyListPushBack(PSinglyListNode* PPHead, SinglyDataType x);

//ͷɾ
void SinglyListPopFront(PSinglyListNode* PPHead);

//βɾ
void SinglyListPopBack(PSinglyListNode* PPHead);

//����
PSinglyListNode SinglyListFind(PSinglyListNode PHead, SinglyDataType val);

//ָ��λ�ò���
//��PPHead�Ϸ�ʱ����pos�ڵ�֮ǰ����
//��PPHeadΪ��ʱ����pos�ڵ�֮�����
void SinglyInsert(PSinglyListNode* PPHead, PSinglyListNode pos, SinglyDataType val);

//ɾ��ָ��λ��
void SinglyErase(PSinglyListNode* PPHead, PSinglyListNode pos);