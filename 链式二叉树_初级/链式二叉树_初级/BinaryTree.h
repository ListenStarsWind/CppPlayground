#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include"Queue.h"
#include"vld.h"


typedef int BTData, * pBTData;
typedef struct BinaryTreeNode
{
	BTData _val;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode, * pBTNode;

pBTNode BuyNode(BTData val);

void PreOrder(pBTNode pRoot);

pBTData InOrder(pBTNode pRoot, int* RetuSize);

void PostOrder(pBTNode pRoot);

void LevelOrder(pBTNode pRoot);

// Note: the second parameter "pCurrent" must be dereferenced to 0 when called,
// and the third parameter "null" is used to define what is null, which is theoretically different from the elements of the array.
pBTNode BTBuild(pBTData pVal, int* pCurrent, BTData null);

// The root node is left empty by the caller.
void BTDestroy(pBTNode pRoot);

int BTSize(pBTNode pRoot);

int TerminalSize(pBTNode pRoot);

int BTHeight(pBTNode pRoot);

// Note: The parameter "k" must be greater than 0.
int BTLevelKSize(pBTNode pRoot, int k);

pBTNode BTFind(pBTNode pRoot, BTData val);

bool BTComplete(pBTNode pRoot);