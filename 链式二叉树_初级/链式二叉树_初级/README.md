# 链式二叉树

## 前言

前面我们就堆做了一些学习，现在该换换口味了，堆的物理结构是顺序表，本文的链式二叉树则是链表。

链式二叉树的组织形式较为复杂，为此我们先不按照之前学习数据结构顺序学习，而是先随手生成一个链式二叉树。以它为研究对象学习链式二叉树的各类操作，等到对链式二叉树足够了解之后，再去学习链式二叉树的真正创建方式

```c
#pragma once

#include<stdlib.h>
#include<stdio.h>

typedef int BTData, * pBTData;
typedef struct BinaryTreeNode
{
	BTData _val;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode, * pBTNode;

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

pBTNode CreateBT(pBTData pArray)
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

int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr0);
	return 0;
}
```

## 二叉树的遍历

对二叉树中各节点的遍历是遵循一定顺序进行的，一共有四种顺序：

- 前序遍历(Preorder Traversal 亦称先序遍历)——访问根结点的操作发生在遍历其左右子树之前。  
- 中序遍历(Inorder Traversal)——访问根结点的操作发生在遍历其左右子树之中（间）。  
- 后序遍历(Postorder Traversal)——访问根结点的操作发生在遍历其左右子树之后。  
- 层序遍历(LevelOrder  Traversal)——自上而下，自左至右逐层访问树的结点的过程就是层序遍历。  

------

### 前序遍历

前序遍历依照——根 左子树 右子树的顺序嵌套遍历。

现有一链式二叉树，如下：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221518251.png)

这棵树的根节点为0，这就是第一个遍历到的节点。这棵树可以分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221531512.png)

对于这颗左子树来说，它的根节点为1，这就是第二个遍历到的节点。同样的，这颗左子树也可以拆分成<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221537582.png)

对于这颗左子树来说，它的根节点为2，这就是第三个遍历到的节点。同样的，这颗左子树也可以拆分成<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221541214.png)

对于这颗左子树来说，它的根节点为NULL，这就是第四个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为2的<span style="color: #00FFFF;">左子树</span>已经遍历完了，现在要遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这就是第五个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为1的<span style="color: #00FFFF;">左子树</span>已经遍历完了，现在要遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221537582.png)

对于这颗右子树来说，它的根节点为NULL，这就是第六个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为0的<span style="color: #00FFFF;">左子树</span>已经遍历完了，现在要遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221531512.png)

对于这颗右子树来说，它的根节点为6，这就是第七个遍历到的节点。同样的，这颗右子树也可以拆分成<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221551558.png)

对于这颗左子树来说，它的根节点为7，这就是第八个遍历到的节点。同样的，这颗左子树也可以拆分成<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221553594.png)

对于这颗左子树来说，它的根节点为NULL，这就是第九个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为7的<span style="color: #00FFFF;">左子树</span>已经遍历完了，现在要遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这就是第十个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为6的<span style="color: #00FFFF;">左子树</span>已经遍历完了，现在要遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221551558.png)

对于这颗右子树来说，它的根节点为10，这就是第十一个遍历到的节点。同样的，这颗右子树也可以拆分成<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221556042.png)

对于这颗左子树来说，它的根节点为NULL，这就是第十二个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为10的<span style="color: #00FFFF;">左子树</span>已经遍历完了，现在要遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这就是第十个遍历到的节点。由于根节点已经为空，所以它无法再拆分了。于是，根节点为6的<span style="color: #00FF7F;">右子树</span>已经遍历完了。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221551558.png)

于是，根节点为0的<span style="color: #00FF7F;">右子树</span>已经遍历完了。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221531512.png)

于是根节点为0的这棵树整个都遍历完了。于是遍历结束了。

代码用递归就行，很简单：

```c
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

int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr0);
	PreOrder(pRoot);
	return 0;
}
```

![image-20240822160631929](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221606047.png)

如你所见，数组里的数并不是乱填的。

### 中序遍历

中序遍历依照——左子树  根 右子树的顺序嵌套遍历。

现有一链式二叉树。同样的，这棵树可以分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221610900.png)

对于这颗左子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221614284.png)

对于这颗左子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221541214.png)

对于这颗左子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第一个遍历到的节点；此时，根节点为2的<span style="color: #00FFFF;">左子树</span>已经被遍历完了，所以遍历根节点，于是节点[2]就成为了第二个遍历的节点，之后，再遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第三个遍历到的节点；此时，根节点为4的<span style="color: #00FFFF;">左子树</span>已经被遍历完了，所以遍历根节点，于是节点[4]就成为了第四个遍历的节点，之后，再遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221614284.png)

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第五个遍历到的节点；此时，根节点为6的<span style="color: #00FFFF;">左子树</span>已经被遍历完了，所以遍历根节点，于是节点[6]就成为了第六个遍历的节点，之后，再遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](C:\Users\21066\Desktop\202408221610900.png)

对于这颗右子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221624452.png)

对于这颗左子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221625516.png)

对于这颗左子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第七个遍历到的节点；此时，根节点为8的<span style="color: #00FFFF;">左子树</span>已经被遍历完了，所以遍历根节点，于是节点[8]就成为了第八个遍历的节点，之后，再遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第九个遍历到的节点；此时，根节点为10的<span style="color: #00FFFF;">左子树</span>已经被遍历完了，所以遍历根节点，于是节点[10]就成为了第十个遍历的节点，之后，再遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221624452.png)

对于这颗右子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221628347.png)

对于这颗左子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第十一个遍历到的节点；此时，根节点为12的<span style="color: #00FFFF;">左子树</span>已经被遍历完了，所以遍历根节点，于是节点[12]就成为了第十二个遍历的节点，之后，再遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第十三个遍历到的节点；此时，根节点为10的树已经被遍历完了。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221631165.png)

也就是说根节点为6的<span style="color: #00FF7F;">右子树</span>也已经被遍历完成，所以根节点为6的树整个都遍历完成了。

代码用递归就行，很简单：

```c
void InOrder(pBTNode pRoot)
{
	if (pRoot == NULL)
	{
		printf("NULL ");
		return;
	}

	InOrder(pRoot->_left);
	printf("%d ", pRoot->_val);
	InOrder(pRoot->_right);
}

int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr1);
	InOrder(pRoot);
	return 0;
}
```

![image-20240822163440773](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221634844.png)

### 后序遍历

后序遍历依照——左子树 右子树  根的顺序嵌套遍历。

现有一链式二叉树，同样的，这棵树可以分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221637148.png)

对于这颗左子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221638922.png)

对于这颗左子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221640560.png)

对于这颗左子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第一个遍历到的节点；此时根节点为3的左子树已经全部遍历完了；于是就遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第二个遍历到的节点；此时根节点为3的左子树和右子树都已经全部遍历完了；于是就遍历它的根节点。于是[3]就是第三个遍历到的节点，

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221638922.png)

此时，根节点为5的左子树已经全部遍历完了，于是就遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第四个遍历到的节点；此时根节点为5的左子树和右子树都已经全部遍历完了；于是就遍历它的根节点。于是[5]就是第五个遍历到的节点，

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221637148.png)

此时，根节点为13的左子树已经全部遍历完了，于是就遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221647133.png)

对于这颗左子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221649821.png)

对于这颗左子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第六个遍历到的节点；此时根节点为8的左子树已经全部遍历完了；于是就遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第七个遍历到的节点；此时根节点为8的左子树和右子树都已经全部遍历完了；于是就遍历它的根节点。于是[8]就是第八个遍历到的节点，

此时，根节点为12的左子树已经全部遍历完了，于是就遍历它的<span style="color: #00FF7F;">右子树</span>。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221647133.png)

对于这颗右子树来说，它可以被分为<span style="color: #00FFFF;">左子树</span>和<span style="color: #00FF7F;">右子树</span>：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221653398.png)

对于这颗左子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第九个遍历到的节点；此时根节点为11的左子树已经全部遍历完了；于是就遍历它的<span style="color: #00FF7F;">右子树</span>。

对于这颗右子树来说，它的根节点为NULL，这意味着，它无法再进行拆分了，所以这个节点就是第十个遍历到的节点；此时根节点为11的左子树和右子树都已经全部遍历完了；于是就遍历它的根节点。于是[11]就是第十一个遍历到的节点，

此时根节点为12树的左右子树都遍历完了，所以遍历它的根节点，于是[12]成了第十二个遍历到节点。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221637148.png)

此时根节点为13树的左右子树都遍历完了，所以遍历它的根节点，于是[13]成了第十三个遍历到节点。

根节点为13的树已经全部遍历完了，于是遍历结束。

代码用递归就行，很简单：

```c
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

int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr2);
	PostOrder(pRoot);
	return 0;
}
```

![image-20240822170109839](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408221701930.png)

函数栈帧可以去看《复杂度讲解》那一篇，里面对于递归函数栈帧的举例可比上面三个复杂多了。

算了，画一下吧。

![image-20240823121447462](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231214711.png)

![无标题](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231256493.jpg)

其中红色代表函数栈帧的开辟，蓝色代表释放。箭头旁的数字代表次序，如果还无法理解，请去看《随笔——函数栈帧》那一篇。

--------

前面三个遍历方式时间复杂度为$O(N)$，空间复杂度为$O(H)$，其中H指二叉树的深度，范围是[$log_2(N+1)$,$N$]，最深的时候就是除终端节点外其它节点度都只有一个，最浅的时候就是满二叉那种。

### 层序遍历

层序遍历和上面不太一样。上面的三种遍历用的都是递归，而这里用的是非递归。

它是采用队列实现的，它的思路是先把根节点的指针存入队列，随后进入循环。循环时，先把队列里存储的树节点指针读出来，再用这个树节点指针找到树节点里的数值并打印出来。随后再把该树节点的两个子节点的指针存入队列，不断循环，直到，队列为空。

现有一链式二叉树，如下

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281423314.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281426030.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281427042.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281429640.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281431738.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281433735.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281433716.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281434349.png)

```c
//这里使用的是《栈和队列》的队列代码
//前置声明
typedef struct BinaryTreeNode BTNode, * pBTNode;

typedef pBTNode QDataType;
typedef struct QueueNode
{
	struct QueueNode* _next;
	QDataType _data;
}QNType, * PQNType;

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
```

```c
void test0()
{
	BTData arr[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT1(arr);
	LevelOrder(pRoot);
}
```

![image-20240828141949248](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281419423.png)

## 求二叉树的节点个数

有两种思路：一是设置一个变量，用这个变量去计数节点数目；二是分治（分而治之）。

先看第一种方法。

首先，需要先确定这个变量在哪定义，又怎么定义。

很明显，变量创建之后要进行初始化，这个初始化只能在第一层函数栈帧里被调用，其它层的栈帧会跳过这个初始化过程，

这个特点使我们想起来了关键字`static`。被`static`所修饰的变量，会变为静态变量，被存储在静态区，不在函数栈帧中，其生命周期将会是整个项目，而且它只会执行一次初始化过程：

```c
int BTSize(pBTNode pRoot)
{
	static int Size = 0;
	if (pRoot == NULL)
		return Size;
	Size++;
	BTSize(pRoot->_left);
	BTSize(pRoot->_right);
	return Size;
}
```

只要不为空，就是有效节点，就能走到`Size++`，被计数一次，之后再去计数它的左子树以及右子树。

```c
int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr0);
	printf("%d\n", BTSize(pRoot));
	return 0;
}
```

![image-20240823143902372](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231439487.png)

看起来能运行，但也只是看起来能运行。

```c
int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr0);
	printf("%d\n", BTSize(pRoot));
	printf("%d\n", BTSize(pRoot));
	return 0;
}
```

![image-20240823144028501](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231440574.png)

因为它只初始化一次，所以在下次使用前，并没有重新复位为0，而是会在原先的数值上继续相加。

还有一个办法是直接把变量定义成全局变量，使用前先把它置为0

```c
int Size = 0;
void BTSize(pBTNode pRoot)
{
	if (pRoot == NULL)
		return;
	Size++;
	BTSize(pRoot->_left);
	BTSize(pRoot->_right);
	return;
}

int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr0);
	BTSize(pRoot);
	printf("%d\n", Size);
	Size = 0;
	BTSize(pRoot);
	printf("%d\n", Size);
	return 0;
}
```

![image-20240823145109940](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231451033.png)

或许，还可以在外围封装一下：

```c
int Size = 0;
void BTSize1(pBTNode pRoot)
{
	if (pRoot == NULL)
		return;
	Size++;
	BTSize1(pRoot->_left);
	BTSize1(pRoot->_right);
	return;
}

int BTSize(pBTNode pRoot)
{
	Size = 0;
	BTSize1(pRoot);
	return Size;
}

int main()
{
	BTData arr0[6] = { 0,1,6,2,7,10 };
	BTData arr1[6] = { 6,4,10,2,8,12 };
	BTData arr2[6] = { 13,5,12,3,8,11 };
	BTData arr3[6] = { 0,1,2,3,5,6 };
	pBTNode pRoot = CreateBT(arr0);
	printf("%d\n", BTSize(pRoot));
	printf("%d\n", BTSize(pRoot));
	return 0;
}
```

![image-20240823150827935](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231508024.png)

但使用前要置0还不是最大的问题，最大的问题是它是一个全局变量，全局变量非常容易出现链接型错误，所以这种方法尽管能用，但还是不合适。

-------

第二种方法体现着分治的思想。什么是分治？分治全称叫做分而治之，它的主旨就是把大问题化成小问题，小问题化成没问题。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231542777.png)

如果要求根节点为[3]的这棵树的节点个数，那那就先求出[3]的左子树节点个数，再加上[3]的右子树节点个数，最后再加上根节点自己这一个节点；同样的，左子树和右子树也可以进一步左子子树右子子树，左子子树和右子子树，又可以被拆成左子子子树和右子子子树……，直到这棵树的根节点为空，那不就一个节点都没有吗？于是，就返回0。

```c
int BTSize(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	return BTSize(pRoot->_left) + BTSize(pRoot->_right) + 1;
}
```

![无标题1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231704833.jpg)

其中红色代表函数栈帧的开辟，蓝色代表释放，黑色代表返回值。

```c
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

void test2()
{
	pBTNode pRoot = CreateBT();
	printf("%d\n", BTSize(pRoot));
}
```

![image-20240823170925033](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231709144.png)

## 求终端节点的个数

```c
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

int TerminalSize(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (Isterminal(pRoot))
		return 1;
	return TerminalSize(pRoot->_left) + TerminalSize(pRoot->_right);
}
```

如果`pRoot`为空，那么这棵树就是空树，空树一个节点都没有，那自然有0个终端节点；如果遇到终端节点，由于终端节点下面没有子节点了，所以终端节点作根节点的树只有1个终端节点；如何去求一个数的终端节点数，很简单，把左子树的终端节点求出来，再把右子树的终端节点求出来，一加就行了。

![image-20240823173044588](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231730713.png)

## 求二叉树的高度

```c
int BTHeight(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	int left = BTHeight(pRoot->_left);
	int right = BTHeight(pRoot->_right);
	int max = left > right ? left : right;
	return max + 1;
}

void test4()
{
	pBTNode pRoot = CreateBT();
	printf("%d\n", BTHeight(pRoot));
}
```

![image-20240823173828645](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231738745.png)

这也简单，空树深度为零，所以返回0；记录一下左子树和右子树的深度，取其中最大的那一个，最后返回的时候别忘了再加上根节点自身的那一层。

有人可能这样写：

```c
int BTHeight(pBTNode pRoot)
{
	if (pRoot == NULL)
		return 0;
	return BTHeight(pRoot->_left) > BTHeight(pRoot->_right) ? BTHeight(pRoot->_left) + 1 : BTHeight(pRoot->_right) + 1;
}
```

一定不能这样写。这样写的话，三目操作符前面部分只能比较大小，不会记录具体数值，所以后面要再把那个较深的子树重算一遍，关键是每一个树的较深子树都要重算，所以与上面的写法相比，这里的时间复杂度是指数级别的增长的，而非简单地线性增长。当二叉树大到一定程度后，这种写法已经和死循环没有区别了。

我打一个形象的比喻：为了庆祝某个节日，校长想举办一个活动：要求全体学生每人完成一项作品。于是，校长把所有院长找来开会，把这件事传达下去，各个院长也把本院的辅导员找来，传达了这件事，各个辅导员把手下的班长找来，传达这件事，各个班长把本班学生找来，开了一个班会。这个作品正是你拿手的领域，于是你兴高采烈地把作品交到了班长那，经过班级评比，大家认为你的作品在全班是最好的，要上报上去，上报的时候发现作品丢了，班长只记得你的作品最好，于是让你再创作一遍，然后交到了辅导员那里。辅导员把手底下几个班的作品比较了一下，觉得你所在班的作品最好，想要往上交的时候，发现作品丢了，于是辅导员要求你所在班的班长再交一下作品，于是班长又让全班重做了一下，比较过后，认为你的更好，想上交的时候，发现作品丢了，只记得你的最好，于是找到你，你又做了一篇。然后交到了辅导员那里，辅导员交到了院长手里，院长觉得你辅导员上交的作品最好，想要上交到校长的时候，发现作品丢了，院长只记得你辅导员上交的作品最好，于是交代你的辅导员再收一遍作业，于是你的辅导员又把手下所有班长叫来，让他们再交一下作业，然后班长让全班重做了作业，比较了之后，认为你的最好，想上交的时候，发现作品丢了，他只记得你的作业最好，于是让你重交了作业。辅导员收到作业之后，认为你所在班的作业最好，想上交的时候，发现作业丢了，他只记得你班交的作业最好，于是找到你班班长，要求再收一遍作业，于是班长又让全班重写了，经过比较，认为你的最好，上交的时候，发现作业丢了，只记得你是最好的，于是又让你重写了一遍……好的，我还没说完，但我已经不想说了，大概就是这个意思，自己去品吧，每个节点在比对完手底下数据后都会丢失数据，所以要重新收集一遍，由于每个节点都是这样，所以额外增加的开销将是以指数级别增长。

## 求特定层的节点数

这也简单，比如说，求一个数第K层的节点数，那就等于左子树第K-1层的节点数再加上右子树第K-1层节点数，那什么时候停止呢？那就是K==1的时候，K==1的时候就来到了要计数的层，除此之外，还要提防树没到K的时候就已经空了。

````c
int BTLevelKSize(pBTNode pRoot, int k)
{
	if (pRoot == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BTLevelKSize(pRoot->_left, k - 1) + BTLevelKSize(pRoot->_right, k - 1);
}
````

```c
void test6()
{
	pBTNode pRoot = CreateBT();
	pBTNode pFind = BTFind(pRoot, 1);
	if (pFind != NULL)
		pFind->_val = 5;
}
```

![image-20240826120335667](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261203823.png)

## 查找

思路也比较简单。采用先序遍历，先看根节点，根节点不是，就看左子树，左子树找不到，就找右子树，还找不到，就真的找不到了。

```c
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
```

```c
void test6()
{
	pBTNode pRoot = CreateBT();
	pBTNode pFind = BTFind(pRoot, 1);
	if (pFind != NULL)
		pFind->_val = 5;
}
```

以下面的二叉树为例：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408231542777.png)

栈帧展开图如下：

![image-20240826124713398](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261247593.png)

![无标题](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261246427.jpg)

-------

测试

![image-20240826124900045](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261249852.png)

![image-20240826124924708](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261249484.png)

废案

```c
pBTNode BTFind(pBTNode pRoot, BTData val)
{
	if (pRoot == NULL)
		return NULL;
	if (pRoot->_val == val)
		return pRoot;
	pBTNode pLeft = BTFind(pRoot->_left, val);
	pBTNode pRight = BTFind(pRoot->_right, val);
	if(pLeft == NULL && pRight == NULL)
        return NULL;
    if(pLeft)
        return pLeft;
    else
        return pRight;
}
```

以降低可读性为代价，减少几行代码的优化：（好像不能叫优化）(〃'▽'〃)

```c
pBTNode BTFind(pBTNode pRoot, BTData val)
{
	if (pRoot == NULL)
		return NULL;
	if (pRoot->_val == val)
		return pRoot;
	pBTNode pLeft = BTFind(pRoot->_left, val);
	if (pLeft)
		return pLeft;
	return BTFind(pRoot->_right, val);
}
```

## 销毁

销毁也是采用分治的思想。先销毁左子树，再销毁右子树，最后销毁根节点。如果根节点为空，则意味着这是一棵空树，空树本身就是被销毁的，所以就停下来。

```c
// The root node is left empty by the caller.
void BTDestroy(pBTNode pRoot)
{
	if (pRoot == NULL)
		return;
	BTDestroy(pRoot->_left);
	BTDestroy(pRoot->_right);
	free(pRoot);
}
```

## 构建二叉树

此处的二叉树构建方法是通过带有空的前序遍历结果反推二叉树。采用的也是分治思想，详情请参考同名项目。

```c
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
```

## 判断是否是完全二叉树

让我们先回顾回顾完全二叉树的两个条件：

- 除最深层外，其它层必须是满的。
- 最深层可以不满，但必须连续。

我们的思路是先向层序遍历那样逐层逐层地读数据，直到读到一个空节点。此时空节点上一层节点的子节点肯定都在队列里了，与空节点同一层节点的子节点也肯定在队列中，然后读出队列中的所有剩余成员，如果剩余成员都为空，一方面可以证明第一个空节点所在的层确实是最后一层，另一方面也可以证明空节点所在的层确实是连续的。

```c
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
```

先来看第一个测试用例：

```c
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
```

易知，该测试用例中的二叉树如下：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311500416.png)

第一个循环负责找到第一个空节点，很明显对于用例来说，是[2]的右节点，进入第二个循环之后，队列中还剩下[ 5, null, null, null]，找到了一个非空节点，于是返回假。

![image-20240831150720003](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311507120.png)

第二个测试用例：

```c
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
```

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311512900.png)

第一个读到的空节点是[5]的右节点，此时队列中剩下的6个节点全为空节点，所以确实是完全二叉树，返回真。

![image-20240831151551189](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311515323.png)

----------

题外话：

这里再补充一下二叉树的一条特殊性质：

对于任一非空二叉树来说，如果度为0的节点数为$n_0$，度为2的节点个数为$n_2$，则有：
$$
n_0=n_2+1
$$
最简单的非空二叉树只有一个节点，此时$n_0=1, n_2 =0$，它们之间的差值为1。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311637113.png)

对这棵树增加终端节点，会有两种情况发生：

- 某个度为0的节点变成度为1的节点，但由于添加的是终端节点，度为0的节点数仍然不变，也就是说$n_0$和$n_2$的相对差值不变。

​										![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311644945.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311645640.png)

- 某个度为1的节点变成度为2的节点，也就是说度为2的节点数增加一个，于此同时，由于增加的是终端节点，所以度为0的节点数也增加一个。它们的相对差值同样不变。

  ![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408311649540.png)

  

这个性质主要是用来做选择题的：

某二叉树共有 399 个结点，其中有 199 个度为 2 的结点，则该二叉树中的叶子结点数为（ ）
A 不存在这样的二叉树
B 200
C 198
D 199  

很明显，选B。

在具有 2n 个结点的完全二叉树中，叶子结点个数为（ ）
A n
B n+1
C n-1
D n/2  

对于一个完全二叉树来说，度为1的节点数只有两个可能值：0或者1，因为完全二叉树是必须连续的，再结合上面的性质，就有
$$
2*n_0-1+n_1 = 2n
$$
很明显，节点数是离散的，或者说它必须是个整数，这意味着，$n_1-1$必须为偶数，所以$n_1=1$，所以答案选择A

一棵完全二叉树的节点数位为531个，那么这棵树的高度为（ ）
A 11
B 10
C 8
D 12  

之前我们说过，一棵完全二叉树的最小节点数为$2^{h-1}$，最多节点数为$2^h-1$，其中$h$指的是深度，或者说高度，接下来要做的就是每个选项试一试，看哪个更有可能。比如若是A，则最小节点数为1024，很明显，对不上题目；若是C，节点数最多是255，对不上；A都不行了，D自然也不行；若是B，最少节点数是512，有可能，在加上其它选项都被排除了，所以就选择B

下列数据结构中，不适合采用顺序存储结构的是（ ）
A 非完全二叉树
B 堆
C 队列
D 栈  

我们的堆和栈就是用顺序表实现的，所以没有异议，关键是选A还是C，一般的队列确实都是用链表实现的，但循环队列恰恰用数组实现更合适，目录在项目文件夹里，不在题目文件夹里，所以选A。不过我个人觉得AC都应选，循环队列用的并不多，这道题感觉在钻牛角尖。

# 完

