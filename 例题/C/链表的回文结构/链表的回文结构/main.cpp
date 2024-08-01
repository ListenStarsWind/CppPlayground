#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>

struct ListNode
{
    int val;
    struct ListNode* next;
};

class PalindromeList {
public:

    struct ListNode* middleNode(struct ListNode* head) {
        struct ListNode* PFast = head;
        struct ListNode* PSlow = head;
        while (PFast && PFast->next) {
            PFast = PFast->next->next;
            PSlow = PSlow->next;
        }
        return PSlow;
    }

    struct ListNode* reverseList(struct ListNode* head) {
        struct ListNode* PLast = NULL;
        struct ListNode* PCurrent = head;
        struct ListNode* PNext = head;
        while (PCurrent) {
            PNext = PCurrent->next;
            PCurrent->next = PLast;
            PLast = PCurrent;
            PCurrent = PNext;
        }
        return PLast;
    }

    bool chkPalindrome(ListNode* A) {
        // write code here
        struct ListNode* mind = middleNode(A);
        struct ListNode* rmind = reverseList(mind);
        while (rmind) {
            if (rmind->val != A->val) {
                return false;
            }
            else {
                rmind = rmind->next;
                A = A->next;
            }
        }
        return true;
    }
};