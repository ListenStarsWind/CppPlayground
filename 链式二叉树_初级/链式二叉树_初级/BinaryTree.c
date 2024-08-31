#include"BinaryTree.h"

pBTNode BuyNode(BTData val)
{
	pBTNode p = (pBTNode)malloc(sizeof(BTNode));
	if (p == NULL)
	{
		perror("BuyNode malloc fail");
		return NULL;
	}
	p->_val = val;
	p->_left = NULL;
	p->_right = NULL;
	return p;
}

void PreOrder(pBTNode pRoot)
{
	if (pRoot == NULL)
	{
		printf("NULL ");
		return;
	}

	printf("%d ", pRoot->_val);
	PreOrder(pRoot->_left);
	PreOrder(pRoot->_right);
}

//void InOrder(pBTNode pRoot)
//{
//	if (pRoot == NULL)
//	{
//		printf("NULL ");
//		return;
//	}
//
//	InOrder(pRoot->_left);
//	printf("%d ", pRoot->_val);
//	InOrder(pRoot->_right);
//}

void _InOrder(pBTNode pRoot, pBTData pArray, int* pCurrent) {
	if (pRoot == NULL)
		return;
	_InOrder(pRoot->_left, pArray, pCurrent);
	pArray[*pCurrent] = pRoot->_val;
	(*pCurrent)++;
	_InOrder(pRoot->_right, pArray, pCurrent);
}

pBTData InOrder(pBTNode pRoot, int* RetuSize) {
	*RetuSize = BTSize(pRoot);
	pBTData pArray = (pBTData)malloc(*RetuSize * sizeof(BTData));
	if (pArray == NULL) {
		perror("InOrder malloc fail");
		return NULL;
	}
	int i = 0;
	_InOrder(pRoot, pArray, &i);
	return pArray;
}

void PostOrder(pBTNode pRoot)
{
	if (pRoot == NULL)
	{
		printf("NULL ");
		return;
	}

	PostOrder(pRoot->_left);
	PostOrder(pRoot->_right);
	printf("%d ", pRoot->_val);
}

void LevelOrder(pBTNode pRoot)
{
	PQType pQueue = QInit();
	QPush(pQueue, pRoot);
	while (QSize(pQueue) != 0)
	{
		pBTNode pCurrent = QReadFront(pQueue);
		printf("%d ", pCurrent->_val);
		QPop(pQueue);
		if (pCurrent->_left)
		{
			QPush(pQueue, pCurrent->_left);
		}
		if (pCurrent->_right)
		{
			QPush(pQueue, pCurrent->_right);
		}
	}
	printf("\n");
	QDestory(pQueue);
}

pBTNode BTBuild(pBTData pVal, int* pCurrent, BTData null) {
	if (pVal[*pCurrent] == null) {
		(*pCurrent)++;
		return NULL;
	}
	pBTNode pRoot = BuyNode(pVal[(*pCurrent)++]);
	pRoot->_left = BTBuild(pVal, pCurrent, null);
	pRoot->_right = BTBuild(pVal, pCurrent, null);
	return pRoot;
}

void BTDestroy(pBTNode pRoot)
{
	if (pRoot == NULL)
		return;
	BTDestroy(pRoot->_left);
	BTDestroy(pRoot->_right);
	free(pRoot);
}

static int NodeDegree(pBTNode pNode)
{
	assert(pNode);
	if (pNode->_left == NULL && pNode->_right == NULL)
		return 0;
	if (pNode->_left == NULL || pNode->_right == NULL)
		return 1;
	if (pNode->_left != NULL && pNode->_right != NULL)
		return 2;
	return EOF;
}

static bool Isterminal(pBTNode pNode)
{
	assert(pNode);
	if (NodeDegree(pNode) == 0)
		return true;
	else
		return false;
}

int BTSize(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	return BTSize(pRoot->_left) + BTSize(pRoot->_right) + 1;
}

int TerminalSize(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (Isterminal(pRoot))
		return 1;
	return TerminalSize(pRoot->_left) + TerminalSize(pRoot->_right);
}

int BTHeight(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	int left = BTHeight(pRoot->_left);
	int right = BTHeight(pRoot->_right);
	int max = left > right ? left : right;
	return max + 1;
}

int BTLevelKSize(pBTNode pRoot, int k)
{
	assert(k > 0);
	if (pRoot == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BTLevelKSize(pRoot->_left, k - 1) + BTLevelKSize(pRoot->_right, k - 1);
}

pBTNode BTFind(pBTNode pRoot, BTData val)
{
	if (pRoot == NULL)
		return NULL;
	if (pRoot->_val == val)
		return pRoot;
	pBTNode pLeft = BTFind(pRoot->_left, val);
	if (pLeft)
		return pLeft;
	pBTNode pRight = BTFind(pRoot->_right, val);
	if (pRight)
		return pRight;
	return NULL;
}

bool BTComplete(pBTNode pRoot)
{
	PQType pQueue = QInit();
	QPush(pQueue, pRoot);
	while (!IsEmptyQueue(pQueue))
	{
		pBTNode pCurrent = QReadFront(pQueue);
		if (pCurrent == NULL)
		{
			QPop(pQueue);
			break;
		}
		QPop(pQueue);
		QPush(pQueue, pCurrent->_left);
		QPush(pQueue, pCurrent->_right);
	}
	while (!IsEmptyQueue(pQueue))
	{
		pBTNode pCurrent = QReadFront(pQueue);
		if (pCurrent != NULL)
		{
			QDestory(pQueue);
			return false;
		}
		QPop(pQueue);
	}
	QDestory(pQueue);
	return true;
}