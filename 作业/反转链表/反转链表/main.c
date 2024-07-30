#define _CRT_SECURE_NO_WARNINGS


/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*/
 
typedef struct ListNode* PListNode;

struct ListNode* reverseList(struct ListNode* head) {
    PListNode PLast = NULL;
    PListNode PCurrent = head;
    PListNode PNext = head;
    while (PCurrent) {
        PNext = PCurrent->next;
        PCurrent->next = PLast;
        PLast = PCurrent;
        PCurrent = PNext;
    }
    return PLast;
}