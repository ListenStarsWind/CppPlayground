#include<stdlib.h> 
#include<stdio.h>

typedef struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode,* pTreeNode;


pTreeNode BuyNode(int val)
{
	pTreeNode p = (pTreeNode)malloc(sizeof(TreeNode));
	if (p == NULL)
	{
		perror("BuyNode malloc fail");
		return NULL;
	}
	p->val = val;
	p->left = NULL;
	p->right = NULL;
	return p;
}

pTreeNode CreateBT1(int* pArray)
{
	pTreeNode p = BuyNode(pArray[0]);
	pTreeNode current = p;
	current->left = BuyNode(pArray[1]);
	current->right = BuyNode(pArray[2]);
	current = current->left;
	current->left = BuyNode(pArray[3]);
	current = p->right;
	current->left = BuyNode(pArray[4]);
	current->right = BuyNode(pArray[5]);
	return p;
}

pTreeNode CreateBT(void)
{
	pTreeNode p1 = BuyNode(3);
	pTreeNode p2 = BuyNode(2);
	pTreeNode p3 = BuyNode(4);
	pTreeNode p4 = BuyNode(8);
	pTreeNode p5 = BuyNode(6);
	pTreeNode p6 = BuyNode(2);
	pTreeNode p7 = BuyNode(1);
	p1->left = p2;
	p1->right = p3;
	p2->left = p4;
	p3->left = p5;
	p3->right = p6;
	p5->left = p7;
	return p1;
}

int BTSize(struct TreeNode* root)
{
	if (root == NULL)
		return 0;
	return BTSize(root->left) + BTSize(root->right) + 1;
}

void _preorderTraversal(struct TreeNode* root, int** pCurrent)
{
	if (root == NULL)
		return;
	int* p = *pCurrent;
	(*pCurrent)++;
	p[0] = root->val;
	_preorderTraversal(root->left, pCurrent);
	_preorderTraversal(root->right, pCurrent);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
	*returnSize = BTSize(root);
	int* pArray = (int*)malloc(*returnSize * sizeof(int));
	int* ret = pArray;
	int** pCurrent = &pArray;
	_preorderTraversal(root, pCurrent);
	return ret;
}

int main()
{
	int arr[6] = { 0,1,6,2,7,10 };
	pTreeNode p = CreateBT1(arr);
	int Size = 0;
	int* pArray = preorderTraversal(p, &Size);
	int cir = 0;
	for (; cir < Size; cir++)
	{
		printf("%d ", pArray[cir]);
	}
	return 0;
}