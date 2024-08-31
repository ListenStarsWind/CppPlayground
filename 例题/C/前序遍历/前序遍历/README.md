# 前序遍历

![image-20240828110132631](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281101808.png)

这和《链式二叉树_初级》里的前序遍历可不是一个东西。这里不是用打印输出数据的，而是输出一个数组，这个数组里存着前序遍历的值。

首先我们需要明确，这里的数组应该是动态开辟出的。为了让开辟出的数组正好能存下所有的值，先计算一下输入二叉树的节点个数，然后以此为依据，用`malloc`一次性开辟出来；若是采用`realloc`的方式开辟，数组容易存不满。

很明显这个动态开辟只用开辟一次，所以整个函数被封为主函数和子函数，主函数写不能重复的部分，子函数写要重复的部分。

接下来的问题是如何让子函数每次迭代一次，数组就写入读到的值。上面的图片使用的是下标这种方法。在主函数里专门定义一个数组的下标，为了让这个下标在子函数的递归过程中都顺利地加一，我们把下标以指针的形式传入到子函数当中。

如果用下标本体会发生什么呢？此时每个子函数栈帧都有自己的下标，此时某个栈帧下标加一，都是对这个栈帧的下标加一，而不会影响别的栈帧的下标。

比如第一层栈帧里的下标加一变成1了，把这个“1”传到第二层栈帧，第二层里的下标加一就变成2了，假如现在就回归了，第二层栈帧释放，回到了第一层栈帧，关键在于，第一层栈帧里的下标还是1，于是第二次进入第二层栈帧的时候，它就会把原先第一次进入第二层栈帧所写入数组的数据覆写掉，于是就完蛋了。

第二种思路是不用指针操控写入的位置，而是直接改变数组首元素地址，每次写入都在下标为0的地方写入，当然，这样要用二级指针，不过这种思路容易受到操作顺序的困扰。

接口`returnSize`是用来接收返回数组元素个数的。

```c
int BTSize(struct TreeNode* root)
{
    if(root == NULL)
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
```

为了让顺序更加确定，指针的解引用和加一被拆成了两行。

另外，该项目下有力扣题目的测试框架，下次可以重新利用。

