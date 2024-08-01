
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

typedef int ListNodeDataType;

typedef struct ListNode
{
	ListNodeDataType data;
	struct ListNode* next;
}ListNode, * PListNode;

PListNode BuyListNode(ListNodeDataType x)
{
	PListNode PNewNode = (PListNode)malloc(sizeof(ListNode));
	if (PNewNode == NULL)
	{
		printf("BuyListNode malloc fail\n");
		return PNewNode;
	}
	PNewNode->data = x;
	PNewNode->next = NULL;
	return PNewNode;
}

//用return而不用二级指针的形式返回是为了尽量维持接口统一性
//为了保护哨兵位，后续增删查改函数统一使用一级指针，并且参数用const修饰
//没有创建新的结构体，ListNodeDataType仍可以根据具体需求更换类型
PListNode ListNodeInit()
{
	ListNodeDataType x;
	size_t cir = sizeof(ListNodeDataType);
	char* p = (char*)(&x);
	while (cir--)
	{
		*p = 0xcd;
		p++;
	}
	p = NULL;
	PListNode PNewNode = BuyListNode(x);
	return PNewNode;
}

void SinglyListPushFront(const PListNode PHead, ListNodeDataType x)
{
	assert(PHead);
	PListNode PNewNode = BuyListNode(x);
	PNewNode->next = PHead->next;
	PHead->next = PNewNode;
}

int main()
{
	PListNode PHead = ListNodeInit();
	SinglyListPushFront(PHead, 5);
	SinglyListPushFront(PHead, 4);
	SinglyListPushFront(PHead, 3);
	SinglyListPushFront(PHead, 2);
	SinglyListPushFront(PHead, 1);
	return 0;
}