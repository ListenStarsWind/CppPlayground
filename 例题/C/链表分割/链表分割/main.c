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


////////////////////////////////////////////////////////////////

typedef struct ListNode ListNode, * PListNode;
	ListNode* partition(ListNode* pHead, int x) {
		// write code here
		struct ListNode* PHigh = (struct ListNode*)malloc(sizeof(struct ListNode));
		struct ListNode* PLow = (struct ListNode*)malloc(sizeof(struct ListNode));
		struct ListNode* TerminateH = PHigh;
		struct ListNode* TerminateL = PLow;
		struct ListNode* Current = pHead;
		while (Current)
		{
			if (Current->val < x)
			{
				TerminateL->next = Current;
				TerminateL = TerminateL->next;
			}
			else
			{
				TerminateH->next = Current;
				TerminateH = TerminateH->next;
			}
			Current = Current->next;
		}
		TerminateH->next = NULL;
		Current = PHigh->next;
		free(PHigh);
		PHigh = Current;
		TerminateL->next = PHigh;
		Current = PLow->next;
		free(PLow);
		PLow = Current;
		return PLow;
	}

////////////////////////////////////////////////////////////////

PListNode BuyNode(int x)
{
	PListNode PNode = (PListNode)malloc(sizeof(ListNode));
	PNode->val = x;
	PNode->next = NULL;
}

int main()
{
	int nums[] = { 6,2,8 };
	PListNode PHead = BuyNode(nums[0]);
	PListNode PLast = PHead;
	PListNode PCurrent = NULL;
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int cir = 0;
	for (cir = 1; cir < numsSize; cir++)
	{
		PCurrent = BuyNode(nums[cir]);
		PLast->next = PCurrent;
		PLast = PCurrent;
	}
	PCurrent = NULL;
	PLast = NULL;
	PCurrent = partition(PHead, 9);
	return 0;
}