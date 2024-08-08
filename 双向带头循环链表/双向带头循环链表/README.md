# 带头双向循环链表

这里的“头”指的是哨兵位，哨兵位不存储有效数据，它可以让链表不会真正为空，也就是一个节点也没有，这样做插入数据时就不用像单链表那样根据链表是否为空分情况考虑；为了实现链表的双向效果，链表节点的指针域将包含两个指针，它们分别指向当前节点的上一个节点和下一个节点；循环则是说链表的尾节点不再指向空，而是指向头结点，即哨兵位，

## 节点定义

```c
typedef int LTDataType;

typedef struct ListNode
{
	struct ListNode* prev;
	struct ListNode* next;
	LTDataType val;
}LT, * PLT;
```

## 尾插

```c
PLT LTInit(void)
{
	PLT head = (PLT)malloc(sizeof(LT));
	if (head == NULL)
	{
		printf("LTInit malloc fail!\n");
		return NULL;
	}
	head->prev = head;
	head->next = head;
	return head;
}

static PLT BuyNode(LTDataType val)
{
	PLT NewNode = (PLT)malloc(sizeof(LT));
	if (NewNode == NULL)
	{
		printf("BuyNode malloc fail!\n");
		return NULL;
	}
	NewNode->prev = NewNode;
	NewNode->next = NewNode;
	NewNode->val = val;
	return NewNode;
}

void LTPushBack(const PLT head, LTDataType val)
{
	assert(head);
	PLT NewNode = BuyNode(val);
	PLT Tail = head->prev;
	Tail->next = NewNode;
	NewNode->prev = Tail;
	head->prev = NewNode;
	NewNode->next = head;
}

void LTPrintf(const PLT head)
{
	assert(head);
	PLT current = head->next;
	while (current != head)
	{
		printf("%d->",current->val);
		current = current->next;
	}
	printf("NULL\n");
}

void LTDest(const PLT head)
{
	assert(head);
	PLT current = head->next;
	PLT next = NULL;
	while (current != head)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(head);
}
```

初始化时头结点指向自己，是为了让链表成环，这样做是为了让初始化的链表和有数据的链表有着相同的组织形式，提高后续函数的泛用性。

## 测试尾插

```c
//Used test "LTPushBack"
void Test1()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 1);
	LTPushBack(head, 2);
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}
```

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408070945766.mp4"></video>

## 头插

```c
void LTPushFront(const PLT head, LTDataType val)
{
	assert(head);
	PLT NewNode = BuyNode(val);
	NewNode->prev = head;
	NewNode->next = head->next;
	NewNode->next->prev = NewNode;
	head->next = NewNode;
}
```

如果是非空链表，那需要改四个指针：头结点的`next`，第一个节点的`prev`，新节点的`prev`和`next`；先改新节点，因为新节点的`next`和`prev`对我们来说是没有实际意义的，改完之后还能起到存储数据的作用，然后再改另外两个。于是就有了上面的代码。

那当链表并不为空，也就是链表只有头结点的时候，上述代码还适用吗？此时`head->next`仍是`head`，前两个指针改过后，新节点的`prev`和`next`都指向头结点，看起来没什么问题；后两个指针改过后，头结点的`prev`指向新节点，`next`也指向新节点，还是没有问题，所以不管链表空不空，都可以用这些代码，如果初始化不自己指向自己就达不到现在的效果。

## 测试头插

```c
//Used test "LTPushFront"
void Test2()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}
```

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408071057381.mp4"></video>

看起来还可以。

## 尾删

```c
void LTPopBack(const PLT head)
{
	assert(head);
	if (head->next == head)
	{
		printf("Thils list is already null!\n");
		return;
	}
	PLT Tail = head->prev;
	head->prev = Tail->prev;
	Tail->prev->next = head;
	free(Tail);
}
```

当只剩下一个存储有效数据的节点时，它依旧可以运行，而且删除之后，链表又回到了刚刚初始化的样子。

## 测试尾删

```c
//Used test "LTPopBack"
void Test3()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	LTPopBack(head);
	LTPopBack(head);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}
```

![image-20240807155405105](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408071554296.png)

通过。

## 头删

```c
void LTPopFront(const PLT head)
{
	assert(head);
	if (head->next == head)
	{
		printf("Thils list is already null!\n");
		return;
	}
	PLT first = head->next;
	head->next = first->next;
	first->next->prev = head;
	free(first);
}
```

## 测试头删

```c
//Used test "LTPopFront"
void Test4()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	LTPopBack(head);
	LTPopBack(head);
	LTPrintf(head);
	LTPopFront(head);
	LTPopFront(head);
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}
```

![image-20240807160243071](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408071602182.png)

效果可以。

## 查找

```c
PLT LTFind(PLT head, LTDataType val)
{
	assert(head);
	PLT current = head->next;
	while (current != head)
	{
		if (current->val == val)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}
```

没什么好说的，查找主要的应用场景是对特定位置进行修改

## 在特定位置之前插入

```c
void LTInsertBefore(PLT pos, LTDataType val)
{
	assert(pos);
	PLT before = pos->prev;
	PLT NewNode = BuyNode(val);
	NewNode->prev = before;
	NewNode->next = pos;
	before->next = NewNode;
	pos->prev = NewNode;
}
```

## 删除特定位置

```c
void LTErase(PLT pos)
{
	assert(pos);
	PLT before = pos->prev;
	PLT after = pos->next;
	before->next = after;
	after->prev = before;
    free(pos);
}
```

当然，这里的`pos`有可能是哨兵位，但这里就不考虑了。

## 测试特定位置插入

```c
//Used test "LTInsertBefore LTErase"
void Test5()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPrintf(head);
	PLT find = LTFind(head, 2);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTInsertBefore(find, 1);
	}
	LTPrintf(head);
	find = LTFind(head, 5);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTInsertBefore(find, 4);
	}
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}
```

![image-20240808091023609](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408080910822.png)

## 使用`LTInsertBefore`实现头插尾插

```c
void LTPushBack(const PLT head, LTDataType val)
{
    LTInsertBefore(head, val);
}

void LTPushFront(const PLT head, LTDataType val)
{
    LTInsertBefore(head->next, val);
}
```

使用`LTInsertBefore`实现链表的快速部署。

## 测试特定位置删除

```c
//Used test "LTErase"
void Test6()
{
	PLT head = NULL;
	head = LTInit();
	LTPushBack(head, 3);
	LTPushBack(head, 4);
	LTPushBack(head, 5);
	LTPushFront(head, 2);
	LTPushFront(head, 1);
	LTPrintf(head);
	PLT find = LTFind(head, 2);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTErase(find);
	}
	LTPrintf(head);
	find = LTFind(head, 3);
	if (find == NULL)
	{
		printf("find fail!\n");
	}
	else
	{
		LTErase(find);
	}
	LTPrintf(head);
	LTDest(head);
	head = NULL;
}
```

![image-20240808093307983](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408080933106.png)

## 使用`LTErase`实现头删尾删

```c
void LTPopBack(const PLT head)
{
	assert(head);
	if (head->next == head)
	{
		printf("Thils list is already null!\n");
		return;
	}
	LTErase(head->prev);
}

void LTPopFront(const PLT head)
{
	assert(head);
	if (head->next == head)
	{
		printf("Thils list is already null!\n");
		return;
	}
	LTErase(head->next);
}
```

使用`LTErase`实现链表的快速部署。