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

typedef struct ListNode* PListNode;
typedef struct ListNode ListNode;

struct ListNode* FindKthToTail(struct ListNode* pListHead, int k) {
	// write code here
	PListNode pLead = pListHead;
	PListNode pLag = pListHead;
	int cir = k;
	while (pLead && cir--)
	{
		pLead = pLead->next;
	}
	if (pLead == NULL)
	{
		return NULL;
	}
	while (pLead)
	{
		pLead = pLead->next;
		pLag = pLag->next;
	}
	return pLag;
}

/*牛客题目已经下架了，这个是LeetCode的答案
* 
int kthToLast(struct ListNode* head, int k) {
	PListNode pLead = head;
	PListNode pLag = head;
	int cir = k;
	while (cir--) {
		pLead = pLead->next;
	}
	while (pLead) {
		pLead = pLead->next;
		pLag = pLag->next;
	}
	return pLag->val;
}

*/

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
	PCurrent = FindKthToTail(PHead, 0);
	return 0;
}