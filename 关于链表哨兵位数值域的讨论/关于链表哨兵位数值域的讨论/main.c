
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

//��return�����ö���ָ�����ʽ������Ϊ�˾���ά�ֽӿ�ͳһ��
//Ϊ�˱����ڱ�λ��������ɾ��ĺ���ͳһʹ��һ��ָ�룬���Ҳ�����const����
//û�д����µĽṹ�壬ListNodeDataType�Կ��Ը��ݾ��������������
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