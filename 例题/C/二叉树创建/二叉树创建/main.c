#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include"vld.h"

typedef char BTData, * pBTData;
typedef struct BinaryTreeNode {
    BTData _val;
    struct BinaryTreeNode* _left;
    struct BinaryTreeNode* _right;
} BTNode, * pBTNode;

pBTNode BuyNode(BTData val) {
    pBTNode p = (pBTNode)malloc(sizeof(BTNode));
    if (p == NULL) {
        perror("BuyNode malloc fail");
        return NULL;
    }
    p->_val = val;
    p->_left = NULL;
    p->_right = NULL;
    return p;
}

// Note: the second parameter "pCurrent" must be dereferenced to 0 when called,
// and the third parameter "null" is used to define what is null, which is theoretically different from the elements of the array.
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

void BTDestroy(pBTNode pRoot) {
    if (pRoot == NULL)
        return;
    BTDestroy(pRoot->_left);
    BTDestroy(pRoot->_right);
    free(pRoot);
}

int BTSize(pBTNode pRoot) {
    if (pRoot == NULL)
        return 0;
    return BTSize(pRoot->_left) + BTSize(pRoot->_right) + 1;
}

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

int main() {
    char pArray[100] = { 0 };
    scanf("%s", pArray);
    char* p = (char*)pArray;
    int Size = 0;
    int i = 0;
    pBTNode pRoot = BTBuild(p, &Size, '#');
    pBTData pVal = InOrder(pRoot, &Size);
    for (; i < Size; i++) {
        printf("%c ", pVal[i]);
    }
    printf("\n");
    free(pVal);
    BTDestroy(pRoot);
    pRoot = NULL;
    return 0;
}