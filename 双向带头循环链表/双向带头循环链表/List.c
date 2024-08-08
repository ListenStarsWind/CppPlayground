#include"List.h"

PLT LTInit(void)
{
	PLT head = (PLT)malloc(sizeof(LT));
	if (head == NULL)
	{
		printf("LTInit malloc fail!\n");
		return NULL;
	}
	head->prev = head;
	head->next = head;
	return head;
}

static PLT BuyNode(LTDataType val)
{
	PLT NewNode = (PLT)malloc(sizeof(LT));
	if (NewNode == NULL)
	{
		printf("BuyNode malloc fail!\n");
		return NULL;
	}
	NewNode->prev = NewNode;
	NewNode->next = NewNode;
	NewNode->val = val;
	return NewNode;
}

//void LTPushBack(const PLT head, LTDataType val)
//{
//	assert(head);
//	PLT NewNode = BuyNode(val);
//	PLT Tail = head->prev;
//	Tail->next = NewNode;
//	NewNode->prev = Tail;
//	head->prev = NewNode;
//	NewNode->next = head;
//}

void LTPrintf(const PLT head)
{
	assert(head);
	PLT current = head->next;
	while (current != head)
	{
		printf("%d->",current->val);
		current = current->next;
	}
	printf("NULL\n");
}

void LTDest(const PLT head)
{
	assert(head);
	PLT current = head->next;
	PLT next = NULL;
	while (current != head)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(head);
}

//void LTPushFront(const PLT head, LTDataType val)
//{
//	assert(head);
//	PLT NewNode = BuyNode(val);
//	NewNode->prev = head;
//	NewNode->next = head->next;
//	NewNode->next->prev = NewNode;
//	head->next = NewNode;
//}

//void LTPopBack(const PLT head)
//{
//	assert(head);
//	if (head->next == head)
//	{
//		printf("Thils list is already null!\n");
//		return;
//	}
//	PLT Tail = head->prev;
//	head->prev = Tail->prev;
//	Tail->prev->next = head;
//	free(Tail);
//}
//
//void LTPopFront(const PLT head)
//{
//	assert(head);
//	if (head->next == head)
//	{
//		printf("Thils list is already null!\n");
//		return;
//	}
//	PLT first = head->next;
//	head->next = first->next;
//	first->next->prev = head;
//	free(first);
//}

PLT LTFind(PLT head, LTDataType val)
{
	assert(head);
	PLT current = head->next;
	while (current != head)
	{
		if (current->val == val)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void LTInsertBefore(PLT pos, LTDataType val)
{
	assert(pos);
	PLT before = pos->prev;
	PLT NewNode = BuyNode(val);
	NewNode->prev = before;
	NewNode->next = pos;
	before->next = NewNode;
	pos->prev = NewNode;
}

void LTErase(PLT pos)
{
	assert(pos);
	PLT before = pos->prev;
	PLT after = pos->next;
	before->next = after;
	after->prev = before;
	free(pos);
}

void LTPushBack(const PLT head, LTDataType val)
{
	LTInsertBefore(head, val);
}

void LTPushFront(const PLT head, LTDataType val)
{
	LTInsertBefore(head->next, val);
}

void LTPopBack(const PLT head)
{
	assert(head);
	if (head->next == head)
	{
		printf("Thils list is already null!\n");
		return;
	}
	LTErase(head->prev);
}

void LTPopFront(const PLT head)
{
	assert(head);
	if (head->next == head)
	{
		printf("Thils list is already null!\n");
		return;
	}
	LTErase(head->next);
}