#define _CRT_SECURE_NO_WARNINGS

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode ListNode;
typedef ListNode* PListNode;
struct ListNode* middleNode(struct ListNode* head) {
	PListNode PFast = head;
	PListNode PSlow = head;
	while (PFast && PFast->next)
	{
		PFast = PFast->next->next;
		PSlow = PSlow->next;
	}
	return PSlow;
}