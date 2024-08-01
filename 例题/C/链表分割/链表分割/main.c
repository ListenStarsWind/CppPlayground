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


////////////////////////////////////////////////////////////////

PListNode BuyNode(int x)
{
	PListNode PNode = (PListNode)malloc(sizeof(ListNode));
	PNode->val = x;
	PNode->next = NULL;
}

int main()
{
	int nums[] = { 1,2,2,1 };
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
	PCurrent = FindKthToTail(PHead, 2);
	return 0;
}