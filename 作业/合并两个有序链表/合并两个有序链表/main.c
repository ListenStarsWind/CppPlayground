#define _CRT_SECURE_NO_WARNINGS


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include<stdlib.h>

struct ListNode
{
	int val;
	struct ListNode* next;
};

//从这里开始覆写
typedef struct ListNode ListNode, * PListNode;

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
	PListNode PHead = (PListNode)malloc(sizeof(ListNode));
	if (PHead == NULL)
	{
		perror("mergeTwoLists malloc fail");
		return NULL;
	}
	PHead->next = NULL;
	PHead->val = 0xcdcdcdcd;
	PListNode PTail = PHead;
	while (list1 && list2)
	{
		if (list1->val < list2->val)
		{
			PTail->next = list1;
			list1 = list1->next;
		}
		else
		{
			PTail->next = list2;
			list2 = list2->next;
		}
		PTail = PTail->next;
	}
	if (list1)
	{
		PTail->next = list1;
	}
	if (list2)
	{
		PTail->next = list2;
	}
	PTail = PHead;
	PHead = PHead->next;
	free(PTail);
	PTail = NULL;
	return PHead;
}