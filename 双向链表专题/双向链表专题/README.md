# 随笔——双向链表专题

[TOC]

## 前言

在之前的学习中，我们了解到链表共有八种分类，但实际上，我们只用其中的两类。一种是之前学习的单链表，具体的来说是不带头单向不循环链表；接下来我们将学习双向链表，更具体的来说是带头双向循环链表。

## 双向链表的结构

双向链表的最小单位是节点，要想知道双向链表的结构，就要从节点下手。与单链表相同，双向链表的节点也包括两部分，一是负责存储数据的数值域，二是负责存储相邻节点地址指针域；不同的是，双向链表的指针域中有两个指针，一是上一个节点的地址，二是下一个节点的指针。

单链表的结构：

![image-20240712122603901](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121226074.png)

双向链表的结构：

![image-20240712122655834](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121226884.png)

其中的head节点是哨兵位或者说头节点，仅起引导作用，不存储数据；`d1 d2 d3`节点存储有效数据。

```c
//命名双向链表中存储数据的类型
//Name the data type stored in the doubly linked list
typedef int DListDataType;

//定义双向链表节点
//Define the doubly linked list node
typedef struct DListNode
{
	DListDataType data;
	struct DListNode* prev;
	struct DListNode* next;
}DListNode;
```

## 双向链表初始化

空链表中的“空”指的是没有有效数据，而不是没有节点。单链表的节点都存储着有效数据，所以空的单链表就是没有节点的链表；双向链表中的头结点并不存储有效数据，所以空的双向链表指的是只有头节点的链表；为了让双向链表变成空的，从而使其具备容纳有效数据的能力，我们需要对双向链表进行初始化。

为了创建一个空节点，我们要先写一个创建节点的函数。这里我们将创建好的新节点指针域都指向新节点本身而不是NULL，从而实现链表的循环。这样写也便于日后的节点插入。（该函数并不被用户直接调用，所以使用static修饰取消外部链接属性）

```c
//创建并初始化节点
//Create and initialize a node
static DListNode* CreaNode(DListDataType x)
{
	DListNode* NewNode = (DListNode*)malloc(sizeof(DListNode));
	if (NewNode == NULL)
	{
		perror("Node creation failed:");
		exit(1);
	}
	NewNode->data = x;
	NewNode->prev = NewNode->next = NewNode;
	return NewNode;
}
```

初始化的双向链表有两种方法回到上一级函数，分别是return和指针，这里暂时只讲指针，return之后再讲。

为了改变上一级函数中链表表头的值，我们使用表头指针的指针，也就是二级指针的类型传参。

```c
void InitDList(DListNode** HeadNode)
{
	//头结点中的数据是无效的，可以传满足参数类型的任意值
	//The data in the head node is invalid; any value that satisfies the parameter type can be passed
	*HeadNode = CreaNode(-1);
}
```

### 模块测试

```c
//模块测试1：InitDList
void test1()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
}
```

![image-20240712140225762](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121402987.png)

![image-20240712140352748](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121403978.png)

![image-20240712140503861](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121405074.png)

![image-20240712140535684](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121405885.png)

测试通过。

## 尾插

为了保护双向链表的头结点，保证其本身不被修改，参数建议使用一级指针。

```c
void InNodeTail(DListNode* phead, DListDataType x)
{
	assert(phead);
	DListNode* newnode = CreaNode(x);
	newnode->next = phead;
	newnode->prev = phead->prev;
	phead->prev->next = newnode;
	phead->prev = newnode;
}
```

### 模块测试

为了更方便地测试，先写双向链表打印函数

```c
void PrintfDList(DListNode* phead)
{
	DListNode* ptemp = phead->next;
	while (ptemp != phead)
	{
		printf("%d->", ptemp->data);
	}
	printf("stop\n");
}
```

本来我的第一个想法是用do while循环，但考虑到那样做每次循环还要判断是否是头结点，就作罢了。

```c
//模块测试2：InNodeTail
void test2()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeTail(HeadNode, 1);
	InNodeTail(HeadNode, 2);
	InNodeTail(HeadNode, 3);
	PrintfDList(HeadNode);
}
```

测试失败，分析，打印函数中缺乏循环变量调整。

```c
void PrintfDList(DListNode* phead)
{
	DListNode* ptemp = phead->next;
	while (ptemp != phead)
	{
		printf("%d->", ptemp->data);
		ptemp = ptemp->next;
	}
	printf("stop\n");
}
```

![image-20240712145117021](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121451165.png)

测试通过。

## 头插

注意，这里的头指的是存储有效数据节点的前面，而不是头结点的前面。

![image-20240712122655834](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121226884.png)

就这张图来说，是`d1`前面。

```c
void InNodeHead(DListNode* phead, DListDataType x)
{
	assert(phead);
	DListNode* newnode = CreaNode(x);
	newnode->prev = phead;
	newnode->next = phead->next;
	phead->next->prev = newnode;
	phead->next = newnode;
}
```

### 模块测试

```c
//模块测试3：InNodeHead
void test3()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode,1);
	PrintfDList(HeadNode);
}
```

![image-20240712150343404](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121503523.png)

测试通过。

## 尾删

```c
int DeTail(DListNode* phead)
{
	assert(phead);
	if (phead->next == phead)
	{
		//这个链表已经空了
		return EOF;
	}
	else
	{
		DListNode* ptemp = phead->prev;
		phead->prev = ptemp->prev;
		ptemp->prev->next = phead;
		free(ptemp);
		ptemp = NULL;
		return 0;
	}
}
```

### 模块测试

```c
//模块测试4：DeTail
void test4()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	while (DeTail(HeadNode) != EOF)
	{
		;
	}
	PrintfDList(HeadNode);
}
```

![image-20240712153556086](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121535190.png)

测试通过

## 头删

```c
int DeHead(DListNode* phead)
{
	assert(phead);
	if (phead->next == phead)
	{
		//这个链表已经空了
		return EOF;
	}
	else
	{
		DListNode* ptemp = phead->next;
		phead->next = ptemp->next;
		ptemp->next->prev = phead;
		free(ptemp);
		ptemp = NULL;
		return 0;
	}
}
```

### 模块测试

```c
//模块测试4：DeHead
void test5()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DeHead(HeadNode);
	PrintfDList(HeadNode);
	DeHead(HeadNode);
	PrintfDList(HeadNode);
	DeHead(HeadNode);
	PrintfDList(HeadNode);
	while (DeHead(HeadNode) != EOF)
	{
		;
	}
	PrintfDList(HeadNode);
}
```

![image-20240712155234074](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121552179.png)

测试通过。

## 查找特定节点

```c
DListNode* FindNode(DListNode* phead, DListDataType x)
{
	assert(phead);
	DListNode* traversal = phead->next;
	while (traversal != phead)
	{
		if (traversal->data == x)
		{
			return traversal;
		}
		traversal = traversal->next;
	}
	return NULL;
}
```

### 模块测试

```c
//模块测试6：FindNode
void test6()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 4);
	PrintfDList(pfind);
}
```

![image-20240712161407767](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121614908.png)

测试通过。

## 在指定节点之后插入

```c
void InAfSpe(DListNode* pos, DListDataType x)
{
	assert(pos);
	DListNode* new = CreaNode(x);
	new->next = pos->next;
	new->prev = pos;
	pos->next = new-next;
	new->next->prev = new;
}
```

### 模块测试

```c
//模块测试7：InAfSpe
void test7()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 1);
	InAfSpe(pfind, 2);
	PrintfDList(HeadNode);
	pfind = FindNode(HeadNode, 4);
	InAfSpe(pfind, 5);
	PrintfDList(HeadNode);
}
```

失败，分析，笔误？

```c
void InAfSpe(DListNode* pos, DListDataType x)
{
	assert(pos);
	DListNode* new = CreaNode(x);
	new->next = pos->next;
	new->prev = pos;
	pos->next = new;
	new->next->prev = new;
}
```

![image-20240712163333194](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121633307.png)

成功

## 在指定位置之前插入

```c
void InBfSpe(DListNode* pos, DListDataType x)
{
	assert(pos);
	DListNode* new = CreaNode(x);
	new->next = pos;
	new->prev = pos->prev;
	pos->prev = new;
	new->prev->next = new;
}
```

### 模块测试

```c
//模块测试8：InBfSpe
void test8()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 3);
	InBfSpe(pfind, 2);
	PrintfDList(HeadNode);
	pfind = FindNode(HeadNode, 6);
	InBfSpe(pfind, 5);
	PrintfDList(HeadNode);
}
```

![image-20240712164507438](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121645555.png)

测试通过

## 删除指定位置节点

注意：逻辑上来讲，为了避免删除哨兵位，理应判断输入节点是否是头结点，但输入节点是由`FindNode`函数得到的，理论上来说，返回值不会是哨兵位，至于在指定位置之前或者之后删除，可能会误删头结点，属于极度危险操作，所以后面不会再写它们。

```c
void DePos(DListNode* pos)
{
	assert(pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
	pos = NULL;
}
```

### 模块测试

```c
//模块测试9：DePos
void test9()
{
	DListNode* HeadNode = NULL;
	InitDList(&HeadNode);
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DListNode* pfind = FindNode(HeadNode, 4);
	DePos(pfind);
	PrintfDList(HeadNode);
}
```

![image-20240712171103809](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121711914.png)

测试通过。

另外，需要注意的是，在该节点被删除后，其对应的指针将会变为野指针，但这里并没有把参数类型设置为二级指针，这是考虑到接口（或者说方法）的一致性，你可以看到，前面的几乎所有函数，其参数都是一级指针，若把`DePos`的参数设置成二级指针，将极大增大使用者的记忆负担，如果将来这些函数要给别人使用时，你就需要特别告诉他，这个函数传的是二级指针，别人会觉得这套函数记起来很麻烦；使用者并不在意函数实现的内在逻辑，只要达到预定效果就行，他不一定非常清楚这些参数到底应该传几级指针。

在构建一类接口时，要尽可能保持使用方法的一致性，减轻记忆负担。



现在我们来以return的方式将初始化的链表传到上一级函数

```c
//双向链表初始化
//Initialize the doubly linked list
#define optimize//使用模块测试0到9时请注释该指令
#ifndef optimize
void InitDList(DListNode** HeadNode);
#else
DListNode* InitDList();
#endif

#ifndef optimize

void InitDList(DListNode** HeadNode)
{
	//头结点中的数据是无效的，可以传满足参数类型的任意值
	//The data in the head node is invalid; any value that satisfies the parameter type can be passed
	*HeadNode = CreaNode(-1);
}

#else

DListNode* InitDList()
{
	DListNode* phead = CreaNode(-1);
	return phead;
}

#endif
```

```c
//模块测试10：DListNode* InitDList()
void test10()
{
	DListNode* HeadNode = NULL;
	HeadNode = InitDList();
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	DeTail(HeadNode);
	PrintfDList(HeadNode);
	while (DeTail(HeadNode) != EOF)
	{
		;
	}
	PrintfDList(HeadNode);
}
```

![image-20240712172353209](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121723317.png)

通过测试。

现在如果别人要用这套函数时，你只需要告诉他，初始化函数不用传参，其他函数都是传入一级指针，删除之后记得把指针置为空。其它的什么参数都好理解，插入数据总不能不传要插入的数据吧。一二级指针可比这些参数要难理解不少。

## 销毁双向链表

其实之前这个都写过，你可以看头删尾删，它们之所以有返回值，就是为了把链表直接置为空，当然，销毁更彻底点，连头结点都要释放，大不了你再手动释放一下？

```c
void DouList(DListNode* phead)
{
	assert(phead);
	DListNode* ptemp = phead->next;
	DListNode* next = NULL;
	while (ptemp != phead)
	{
		next = ptemp->next;
		free(ptemp);
		ptemp = next;
	}
	free(phead);
	phead = NULL;
}
```

### 模块测试

```c
//模块测试11：DouList
void test11()
{
	DListNode* HeadNode = NULL;
	HeadNode = InitDList();
	InNodeHead(HeadNode, 3);
	InNodeHead(HeadNode, 2);
	InNodeHead(HeadNode, 1);
	InNodeTail(HeadNode, 4);
	InNodeTail(HeadNode, 5);
	InNodeTail(HeadNode, 6);
	PrintfDList(HeadNode);
	DouList(HeadNode);
	HeadNode = NULL;
}
```

![image-20240712180237988](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121802277.png)

![image-20240712180421704](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121804931.png)

![image-20240712180520024](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121805226.png)

![image-20240712180539996](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407121805200.png)

测试通过。
