#define _CRT_SECURE_NO_WARNINGS

#include"SinglyList.h"

void SinglyListPrintf(PSinglyListNode PHead)
{
	PSinglyListNode PCurrent = PHead;
	while (PCurrent)
	{
		printf("%d ",PCurrent->data);
		PCurrent = PCurrent->next;
	}
	printf("\n");
}

static PSinglyListNode SinglyListNodeGet(SinglyDataType x)
{
	PSinglyListNode PNewNode = (PSinglyListNode)malloc(sizeof(SinglyListNode));
	if (PNewNode == NULL)
	{
		perror("SinglyListGet malloc fail");
		return NULL;
	}
	PNewNode->data = x;
	PNewNode->next = NULL;
	return PNewNode;
}

void SinglyListPushFront(PSinglyListNode* PPHead, SinglyDataType x)
{
	assert(PPHead);
	PSinglyListNode PNewNode = SinglyListNodeGet(x);
	PNewNode->next = *PPHead;
	*PPHead = PNewNode;
}

void SinglyListDestroy(PSinglyListNode* PPDie)
{
	assert(PPDie);
	PSinglyListNode PNextNode = NULL;
	while (*PPDie)
	{
		PNextNode = (*PPDie)->next;
		free(*PPDie);
		*PPDie = PNextNode;
	}
}

void SinglyListPushBack(PSinglyListNode* PPHead, SinglyDataType x)
{
	assert(PPHead);
	PSinglyListNode PNewNode = SinglyListNodeGet(x);
	if (*PPHead == NULL)
	{
		*PPHead = PNewNode;
	}
	else
	{
		PSinglyListNode PEnd = *PPHead;
		while (PEnd->next)
		{
			PEnd = PEnd->next;
		}
		PEnd->next = PNewNode;
	}
}

void SinglyListPopFront(PSinglyListNode* PPHead)
{
	assert(PPHead && *PPHead);
	PSinglyListNode PStart = *PPHead;
	*PPHead = PStart->next;
	free(PStart);
	PStart = NULL;
}

void SinglyListPopBack(PSinglyListNode* PPHead)
{
	assert(PPHead && *PPHead);
	PSinglyListNode PLast = *PPHead;
	PSinglyListNode PTerminal = *PPHead;
	int IsANode = 1;
	while (PTerminal->next)
	{
		PLast = PTerminal;
		PTerminal = PTerminal->next;
		IsANode = 0;
	}
	PLast->next = NULL;
	free(PTerminal); 
	PTerminal = NULL;
	if (IsANode)
	{
		*PPHead = NULL;
	}
}