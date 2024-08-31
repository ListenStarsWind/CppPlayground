#include"BinaryTree.h"

pBTNode CreateBT1(pBTData pArray)
{
	pBTNode p = BuyNode(pArray[0]);
	pBTNode current = p;
	current->_left = BuyNode(pArray[1]);
	current->_right = BuyNode(pArray[2]);
	current = current->_left;
	current->_left = BuyNode(pArray[3]);
	current = p->_right;
	current->_left = BuyNode(pArray[4]);
	current->_right = BuyNode(pArray[5]);
	return p;
}

pBTNode CreateBT(void)
{
	pBTNode p1 = BuyNode(3);
	pBTNode p2 = BuyNode(2);
	pBTNode p3 = BuyNode(4);
	pBTNode p4 = BuyNode(8);
	pBTNode p5 = BuyNode(6);
	pBTNode p6 = BuyNode(2);
	pBTNode p7 = BuyNode(1);
	p1->_left = p2;
	p1->_right = p3;
	p2->_left = p4;
	p3->_left = p5;
	p3->_right = p6;
	p5->_left = p7;
	return p1;
}


void test0()
{
	BTData arr[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT1(arr);
	LevelOrder(pRoot);
}

void test1()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT1(arr0);
	printf("%d\n", BTSize(pRoot));
	printf("%d\n", BTSize(pRoot));
}

void test2()
{
	pBTNode pRoot = CreateBT();
	printf("%d\n", BTSize(pRoot));
}

void test3()
{
	pBTNode pRoot = CreateBT();
	printf("%d\n", TerminalSize(pRoot));
}

void test4()
{
	pBTNode pRoot = CreateBT();
	printf("%d\n", BTHeight(pRoot));
}

void test5()
{
	pBTNode pRoot = CreateBT();
	printf("%d\n", BTLevelKSize(pRoot, 4));
}


void test6()
{
	pBTNode pRoot = CreateBT();
	pBTNode pFind = BTFind(pRoot, 1);
	if (pFind != NULL)
		pFind->_val = 5;
}

void test7()
{
	BTData arr[6] = { 6,4,10,2,8,12 };
	pBTNode pRoot = CreateBT1(arr);
	int Size, i = 0;
	pBTData pArray = InOrder(pRoot, &Size);
	for (; i < Size; i++)
	{
		printf("%d ", pArray[i]);
	}
	printf("\n");
	free(pArray);
	BTDestroy(pRoot);
	pRoot = NULL;
}

void test8()
{
	BTData null = 0;
	int current = 0;
	BTData arr[] = { 1,2,3,0,0,0,4,5,0,0,0 };
	pBTNode pRoot = BTBuild(arr, &current, null);
	if (BTComplete(pRoot))
	{
		printf("It's a fully binary tree.\n");
	}
	else
	{
		printf("It's not a full binary tree.\n");
	}
	BTDestroy(pRoot);
	pRoot = NULL;
}

void test9()
{
	BTData null = 0;
	int current = 0;
	BTData arr[] = { 1,2,3,0,0,4,0,0,5,6,0,0,0 };
	pBTNode pRoot = BTBuild(arr, &current, null);
	if (BTComplete(pRoot))
	{
		printf("It's a fully binary tree.\n");
	}
	else
	{
		printf("It's not a full binary tree.\n");
	}
	BTDestroy(pRoot);
	pRoot = NULL;
}

int main()
{
	test9();
	return 0;
}