# [设计循环链表](https://leetcode.cn/problems/design-circular-queue/description/)

![image-20240813094119043](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408130941298.png)

它更像一个新的项目，而非例题和作业，所以我把它放在了项目文件夹下。

设计你的循环队列实现。 循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。

你的实现应该支持如下操作：

- `MyCircularQueue(k)`: 构造器，设置队列长度为 k 。
- `Front`: 从队首获取元素。如果队列为空，返回 -1 。
- `Rear`: 获取队尾元素。如果队列为空，返回 -1 。
- `enQueue(value)`: 向循环队列插入一个元素。如果成功插入则返回真。
- `deQueue()`: 从循环队列中删除一个元素。如果成功删除则返回真。
- `isEmpty()`: 检查循环队列是否为空。
- `isFull()`: 检查循环队列是否已满。

与我们之前写的队列一样，它也可以通过数组或链表来实现，但由于它是静态的，内存大小一旦确定就不能更改，用链表反而会比用数组麻烦，接下来，我们先通过链表来实现项目，再通过数组来实现。

## 链表

链表具有天然的环形属性，注意，此处链表是不带头单向循环链表。插入数据时往`Rear`上插入，弹出数据时，让`Front`往后迭代，也就是说，`Front`和`Rear`之间的节点才是合法数据。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408131339375.mp4"></video>



### 麻烦一

如何确定队列是满的？

空的时候好理解，此时`Front`和`Rear`指向同一片位置

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408131100960.png)

那现在再加一个数会如何呢？

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408131105696.png)

是不是`Front`和`Rear`又指向同一片位置了？这与队列空的定义相冲突，所以我们把`Rear`的下一次迭代（对于链表来说，是`Rear->_next`）为`Front`定义为满。这意味着，如果我们要存储11个成员，那就要开辟12个空间，`Front`前面的空间不会被使用。下面的代码（链表和数组）将会以这种方式去定义满。

当然，除了这种方式之外，还可以定义一个`_Size`用于描述目前存储数据的个数。在此就不细说了。

### 麻烦二

由于链表节点的内存地址并不是连续的，所以在构造队列时，不能一次性开辟，而要用循环一个一个地开辟节点，再把它们连起来。

### 麻烦三

和《栈和队列》一样，这里的`_Rear`实际上并不指向最后一个节点，而是指向入队时被写入数据的节点，所以访问最后一个节点时，要从头开始遍历。毕竟这是单向链表吗，当然，你也可以把单向链表改为双向链表，不过我个人认为，这里用双向链表实际上也只能在这里派上用场，遍历就遍历吧，犯不着用双向链表。

### 代码如下

```c
typedef int CQData;

typedef struct cListNode {
    CQData _val;
    struct cListNode* _next;
} ListNode, *PListNode;

typedef struct {
    PListNode _pFront;
    PListNode _pRear;
    int _Capacity;
    int _Size;
} MyCircularQueue;

typedef MyCircularQueue* PMyCircularQueue;

// The parameter "k" is used to describe the maximum number of elements that the
// queue can hold.
MyCircularQueue* myCircularQueueCreate(int k);

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value);

bool myCircularQueueDeQueue(MyCircularQueue* obj);

int myCircularQueueFront(MyCircularQueue* obj);

int myCircularQueueRear(MyCircularQueue* obj);

bool myCircularQueueIsEmpty(MyCircularQueue* obj);

bool myCircularQueueIsFull(MyCircularQueue* obj);

void myCircularQueueFree(MyCircularQueue* obj);

static PListNode BuyNode() {
    PListNode p = (PListNode)malloc(sizeof(ListNode));
    if (p == NULL) {
        perror("BuyNode fail");
        return NULL;
    }
    return p;
}

MyCircularQueue* myCircularQueueCreate(int k) {
    PMyCircularQueue p = (PMyCircularQueue)malloc(sizeof(MyCircularQueue));
    if (p == NULL) {
        perror("myCircularQueueCreate fail");
        return NULL;
    }
    p->_Capacity = k;
    p->_Size = 0;

    PListNode pn = BuyNode();
    PListNode pTail = pn;
    p->_pFront = pn;
    p->_pRear = pn;
    while (k--) {
        pn = BuyNode();
        pTail->_next = pn;
        pTail = pTail->_next;
    }
    pTail->_next = p->_pFront;
    return p;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    assert(obj);
    if (myCircularQueueIsFull(obj)) {
        return false;
    } else {
        obj->_pRear->_val = value;
        obj->_pRear = obj->_pRear->_next;
        obj->_Size++;
        return true;
    }
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    assert(obj);
    if (myCircularQueueIsEmpty(obj)) {
        return false;
    } else {
        obj->_pFront = obj->_pFront->_next;
        obj->_Size--;
        return true;
    }
}

int myCircularQueueFront(MyCircularQueue* obj) {
    assert(obj);
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    } else {
        return obj->_pFront->_val;
    }
}

int myCircularQueueRear(MyCircularQueue* obj) {
    assert(obj);
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    } else {
        PListNode pTail = obj->_pFront;
        while (pTail->_next != obj->_pRear) {
            pTail = pTail->_next;
        }
        return pTail->_val;
    }
}
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    assert(obj);
    return obj->_pRear == obj->_pFront;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    assert(obj);
    return obj->_pRear->_next == obj->_pFront;
}

void ListDestory(PListNode pList) {
    assert(pList);
    PListNode pHead = pList;
    PListNode pNext = NULL;
    do {
        pNext = pList->_next;
        free(pList);
        pList = pNext;
    } while (pList != pHead);
}

void myCircularQueueFree(MyCircularQueue* obj) {
    assert(obj);
    ListDestory(obj->_pFront);
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/
```

注意，这里是`LeetCode`上的代码，与VS上的源代码并不完全相同，`LeetCode`确实通过了，VS的解决方案也没有报错，所以就不在VS上进行测试了。但考虑力扣和VS环境并不相同，再加上力扣只测试了它的要求，没有测试我自己的额外功能，所以日后如果使用，必须要小心。比如力扣在读取队头和队尾数据时，直接使用`int`返回，导致这两个接口通用性不足。此外，力扣对队列为空时读取失败，强制要求返回-1；还有力扣服务器中已经对链表进行了自己的定义，所以为了避免重命名，力扣代码是对VS上源代码做出修改的，日后进行拷贝时，切记要拷贝源代码，而非本文档上面的示例。

## 数组

数组与链表不同，它没有天然的环形属性，所以要让`Rear`和`Front`这两个下标，以成员个数为模，比如，要构造容纳5个int的队列，那就要开辟6个int的数组，在这个数组中，0到5才是合法下标，所以在对`Rear`和`Front`这两个下标进行修改时，都要进行模运算形式的修改，保证它们始终是合法的。

数组成员地址连续，所以可以一次性开辟，不用像链表那样一个一个节点地开辟。

数组也不用像链表那样需要遍历才能访问最后一个数据，直接访问即可。

数组的组织形式也比链表要简单，简单意味着可靠，出问题的可能性更低。

### 代码如下

```c
typedef int CQData;

typedef struct {
	CQData* _pArray;
	int _Front;
	int _Rear;
	int _Capacity;
	int _Size;
} MyCircularQueue;

typedef MyCircularQueue* PMyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k);

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value);

bool myCircularQueueDeQueue(MyCircularQueue* obj);

int myCircularQueueFront(MyCircularQueue* obj);

int myCircularQueueRear(MyCircularQueue* obj);

bool myCircularQueueIsEmpty(MyCircularQueue* obj);

bool myCircularQueueIsFull(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k)
{
	PMyCircularQueue p = (PMyCircularQueue)malloc(sizeof(MyCircularQueue));
	if (p == NULL)
	{
		perror("myCircularQueueCreate malloc fail");
		return NULL;
	}

	CQData* arr = (CQData*)malloc(sizeof(CQData)*(k+1));
	if (arr == NULL)
	{
		printf("Warning: Memory Leak.\n");
		perror("Array malloc fail");
		return NULL;
	}

	p->_pArray = arr;
	p->_Front = 0;
	p->_Rear = 0;
	p->_Size = 0;
	p->_Capacity = k;
	return p;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	assert(obj);
	if (myCircularQueueIsFull(obj))
	{
		return false;
	}
	else
	{
		obj->_pArray[obj->_Rear] = value;
		obj->_Rear = (obj->_Rear + 1) % (obj->_Capacity + 1);
		obj->_Size++;
		return true;
	}
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return false;
	}
	else
	{
		obj->_Front = (obj->_Front + 1) % (obj->_Capacity + 1);
		obj->_Size--;
		return true;
	}
}

int myCircularQueueFront(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	return obj->_pArray[obj->_Front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
	assert(obj);
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	return obj->_pArray[(obj->_Rear + obj->_Capacity) % (obj->_Capacity + 1)];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	assert(obj);
	return obj->_Front == obj->_Rear;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
	assert(obj);
	return ((obj->_Rear + 1) % (obj->_Capacity + 1)) == obj->_Front;
}

void myCircularQueueFree(MyCircularQueue* obj) {
	assert(obj);
	free(obj->_pArray);
	free(obj);
}
/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/
```

我们通过"%"来进行模运算。当`Rear`和`Front`这两个下标发生变化后，就要把变化后的结果模上数组的元素个数。可以从代码上看到，这两个下标向后迭代的形式都是`(obj->_Subscript + 1) % (obj->_Capacity + 1)`。比如说，现在要构造一个可以容纳5个数的队列，即k=5，那就需要开辟`sizeof(int)*(k+1)`的数组，也就是说，下标的模就是6。试想一下，一个数模6得到的结果不就是0到5吗，都是合法的下标。

当需要访问队尾数据时，就需要找到`_Rear`的前一个下标，怎么找呢？有两种大方向。做个形象的类比，从中国到美国，既可以向东走，跨过太平洋；也可以向西走，先跨过亚欧大陆，再跨过大西洋。所以既可以让`_Rear`-1再取模，也可以加5再取模，上面的代码是用后一种方法的，即`(obj->_Rear + obj->_Capacity) % (obj->_Capacity + 1)`,为什么要用后一种方法呢？因为计算机科学中的取模和数学里的取模并不完全一样，计算机做不了负数取模，比如，现在`_Rear`已经是0了，减一就变成-1了，对于数学来说，对-1模6确实是5，但计算机-1模6结果是-1，很明显-1是非法下标，会造成越权访问的，用后一种方法就不会有负数取模的出现。

![image-20240813154512465](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408131545709.png)

和链表相同，注意队尾队头读取函数，拷贝时不要拷贝上面的示例，而是要拷贝源代码。代码未经过全面测试，目前只能确定在力扣的题目中没有问题。