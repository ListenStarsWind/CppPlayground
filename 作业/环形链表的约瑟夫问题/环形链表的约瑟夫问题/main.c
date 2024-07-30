#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>

//牛客已定义链表节点
struct ListNode
{
	int val;
	struct ListNode* next;
};

//从这里开始覆写到牛客上

typedef struct ListNode ListNode;
typedef ListNode* PListNode;

PListNode BuyNode(int x)
{
	PListNode PNewNode = (PListNode)malloc(sizeof(ListNode));
	if (PNewNode == NULL)
	{
		perror("BuyNode malloc fail");
		return NULL;
	}
	PNewNode->val = x;
	PNewNode->next = NULL;
	return PNewNode;
}

PListNode CreateList(int n)
{
	PListNode PHead = BuyNode(1);
	PListNode PTail = PHead;
	int cir = 0;
	for (cir = 2; cir <= n; cir++)
	{
		PTail->next = BuyNode(cir);
		PTail = PTail->next;
	}
	PTail->next = PHead;
	return PTail;
}

int ysf(int n, int m) {
	// write code here
	PListNode prev = CreateList(n);
	PListNode head = prev->next;
	PListNode current = head;
	int flag = 0;
	while (prev != current)
	{
		flag++;
		if (flag == m)
		{
			prev->next = current->next;
			free(current);
			current = prev->next;
			flag = 0;
		}
		else
		{
			current = current->next;
			prev = prev->next;
		}
	}
	return current->val;
}