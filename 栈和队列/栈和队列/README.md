[TOC]

# 栈和队列

## 栈

栈是一种特殊的线性结构，其只允许在固定的一端进行插入和删除元素操作。**进行数据插入和删除操作的一端
称为栈顶，另一端称为栈底。**  也就是说，栈中的数据元素遵守后进先出LIFO（Last In First Out）的原则。  

压栈：栈的插入操作叫做进栈/压栈/入栈，**入数据在栈顶**。  

出栈：栈的删除操作叫做出栈。**出数据也在栈顶**。  

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408091021952.mp4"></video>

## 栈的实现

栈的实现一般可以使用**数组或者链表实现**，相对而言数组的结构实现更优一些。因为数组在尾上插入数据的代价比较小。  

栈的实现较为简单，所以相关代码这里一次性给出

```c
//Stack.c
#include"Stack.h"

PST STInit(void)
{
	PST ret = (PST)malloc(sizeof(ST));
	if (ret == NULL)
	{
		perror("Init fail!");
		return NULL;
	}
	ret->_top = 0;
	ret->_capacity = 0;
	ret->_val = NULL;
	return ret;
}

void STDestroy(PST stack)
{
	assert(stack);
	free(stack->_val);
	stack->_val = NULL;
	stack->_top = 0;
	stack->_capacity = 0;
	free(stack);
}

_Bool STEmpty(PST stack)
{
	assert(stack);
	return stack->_top == 0;
}

void STPush(PST stack, STDataType val)
{
	assert(stack);
	if (stack->_top == stack->_capacity)
	{
		int newCapacity = stack->_capacity == 0 ? 4 : 2*stack->_capacity;
		STDataType* p = (STDataType*)realloc(stack->_val, sizeof(STDataType)*newCapacity);
		if (p == NULL)
		{
			perror("extend fail");
			return;
		}
		stack->_val = p;
		stack->_capacity = newCapacity;
	}
	stack->_val[stack->_top] = val;
	stack->_top++;
}

STDataType STPop(PST stack)
{
	assert(stack);
	if (STEmpty(stack))
	{
		printf("The stack already null!\n");
		return;
	}
	else
	{
		STDataType ret = stack->_val[stack->_top-1];
		STDataType* overwriting = (STDataType*)realloc(NULL, sizeof(STDataType));
		if (overwriting == NULL)
		{
			perror("overwriting fail");
		}
		else
		{
			stack->_val[stack->_top-1] = *overwriting;
			free(overwriting);
		}
		stack->_top--;
		return ret;
	}
}

int STSize(PST stack)
{
	assert(stack);
	return stack->_top;
}

void STPopAll(PST stack)
{
	assert(stack);
	while (STSize(stack))
	{
		STDataType val = STPop(stack);
		printf("%d--",val);
	}
	printf("NULL\n");
}
```

```c
//Stack.h
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<stdio.h>

typedef int STDataType;
typedef struct Stack
{
	STDataType* _val;
	int _top;
	int _capacity;
}ST, * PST;

PST STInit(void);

void STDestroy(PST stack);

_Bool STEmpty(PST stack);

void STPush(PST stack, STDataType val);

STDataType STPop(PST stack);

int STSize(PST stack);

void STPopAll(PST stack);
```

```c
//Test.c
#include"Stack.h"

void test1()
{
	PST stack = STInit();
	STPush(stack, 1);
	STPush(stack, 2);
	STPush(stack, 3);
	STPush(stack, 4);
	printf("%d\n",STPop(stack));
	STPopAll(stack);
	stack = NULL;
}

int main()
{
	test1();
	return 0;
}
```

主要思路就是在堆上动态开辟栈，不够就用`realloc`扩容，以数组的形式去组织数据。

有些点要注意：

有些资料的`_top`可能会被叫做`_size`，意为有效数据的个数。`_top`的初始化分为两种，上述代码的初始化方式是依据示意视频的，`_top`指向的是数组中的最后一个成员的末尾地址（地址被简化成了数组下标），因此当栈为空时`_top`被初始化成0；除此之外，`_top`也可以指向最后数组中的最后一个成员，更准确的来说，是最后一个成员的起始地址处，而当栈为空是，由于根本没有成员可以指向，所以`_top`将被初始化成-1，这也是此处`_top`不取名`_size`的原因，哪有大小为负数的？

因为上述代码使用的是第一种初始化方式，所以在取数据，或者说出栈时，实际访问下标是`_top-1`。另外还需注意，不要对空栈出栈。

在出栈时，其实只需要把`_top`减减就行，上述底代码的覆写操作，是为了将不需要的数据初始化成原来的样子，那些数据所处的内存块最开始就是用`realloc`开辟的，在VS上，`realloc`会对开辟的内存快进行初始化，使之全部被初始化成`0xcd`，这里对删除（或者说弹出）数据不手动覆写成`0xcd`，有两个原因，一是麻烦，二是初始化成`0xcd`只是VS的做法，其他开发环境不一定这样做，这样做是为了提高通用性，此外也比直接手动覆写`0xcd`更好理解。

下面是调试视频。可以仔细观察。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408091108124.mp4"></video>

下面找个[题目](https://leetcode.cn/problems/valid-parentheses/description/)做

![image-20240809124344340](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408091243592.png)

这个用栈解决，既容易，也好理解。思路很简单。遇到左括号的字符，即"(""[""{"时，执行入栈操作，当遇到右括号的字符时，弹出一个字符，去拿弹出的字符与读到的右括号字符比对一下，看看是不是配对的。

当然，还有一些小细节，比如说，如果没有左括号字符怎么办，没有右括号又怎么办，这些都需要考虑一番，但都不是什么大问题。

```c
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef char STDataType;
typedef struct Stack {
    STDataType* _val;
    int _top;
    int _capacity;
} ST, *PST;

PST STInit(void) {
    PST ret = (PST)malloc(sizeof(ST));
    if (ret == NULL) {
        perror("Init fail!");
        return NULL;
    }
    ret->_top = 0;
    ret->_capacity = 0;
    ret->_val = NULL;
    return ret;
}

void STDestroy(PST stack) {
    assert(stack);
    free(stack->_val);
    stack->_val = NULL;
    stack->_top = 0;
    stack->_capacity = 0;
    free(stack);
}

_Bool STEmpty(PST stack) {
    assert(stack);
    return stack->_top == 0;
}

void STPush(PST stack, STDataType val) {
    assert(stack);
    if (stack->_top == stack->_capacity) {
        int newCapacity = stack->_capacity == 0 ? 4 : 2 * stack->_capacity;
        STDataType* p =
            (STDataType*)realloc(stack->_val, sizeof(STDataType) * newCapacity);
        if (p == NULL) {
            perror("extend fail");
            return;
        }
        stack->_val = p;
        stack->_capacity = newCapacity;
    }
    stack->_val[stack->_top] = val;
    stack->_top++;
}

STDataType STPop(PST stack) {
    assert(stack);
    if (STEmpty(stack)) {
        printf("The stack already null!\n");
        return 0;
    } else {
        STDataType ret = stack->_val[stack->_top - 1];
        STDataType* overwriting =
            (STDataType*)realloc(NULL, sizeof(STDataType));
        if (overwriting == NULL) {
            perror("overwriting fail");
        } else {
            stack->_val[stack->_top - 1] = *overwriting;
            free(overwriting);
        }
        stack->_top--;
        return ret;
    }
}

int STSize(PST stack) {
    assert(stack);
    return stack->_top;
}

bool isValid(char* s) {
    PST stack = STInit();
    while (*s) {
        if (*s == '(' || *s == '[' || *s == '{') {
            STPush(stack, *s);
        } else {
            if (STSize(stack)) {
                char ch = STPop(stack);
                if (ch == '(' && *s == ')' || ch == '[' && *s == ']' ||
                    ch == '{' && *s == '}') {
                    ;
                } else {
                    STDestroy(stack);
                    return false;
                }
            } else {
                STDestroy(stack);
                return false;
            }
        }
        s++;
    }
    if (STSize(stack)) {
        STDestroy(stack);
        return false;
    } else {
        STDestroy(stack);
        return true;
    }
}
```

## 队列

队列：只允许在一端进行插入数据操作，在另一端进行删除数据操作的特殊线性表，队列具有先进先出FIFO(First In First Out) 入队列：进行插入操作的一端称为**队尾** 出队列：进行删除操作的一端称为**队头**  。

![image-20240812092542464](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408120925555.png)

队列和栈可就不一样了，如果入栈顺序是1234，出栈顺序可不一定是1234，比如，可以先让12入栈，再让2出栈，再让34入栈，再让431出栈，这样出栈顺序就是2431,；而队列出队顺序就一定是1234.

## 队列的实现

队列也可以用数组或链表实现，不过由于它先入先出的性质，用数组的话会有数据的移动，所以主要用链表，而且只要用个精简的链表就行了。

```c
//Queue.h
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

typedef int QDataType;
typedef struct QueueNode
{
	struct QueueNode* _next;
	QDataType _data;
}QNType, * PQNType;

typedef struct Quenu
{
	PQNType _phead;
	PQNType _ptail;
	int _size;
}QType, * PQType;

PQType QInit(void);

void QDestory(PQType pq);

void QPush(PQType pq, QDataType val);

int QSize(PQType pq);

void QPop(PQType pq);

QDataType QReadFront(PQType pq);

QDataType QReadBack(PQType pq);
```

```c
//Queue.c
#include"Queue.h"

PQType QInit(void)
{
	PQType pq = (PQType)malloc(sizeof(QType));
	if (pq == NULL)
	{
		perror("QInit malloc fail");
		return NULL;
	}
	PQNType p = (PQNType)malloc(sizeof(QNType));
	if (p == NULL)
	{
		free(pq);
		perror("QInit SeqList head malloc fail");
		return NULL;
	}
	p->_next = NULL;
	pq->_phead = p;
	pq->_ptail = p;
	pq->_size = 0;
	return pq;
}

void QDestory(PQType pq)
{
	assert(pq);
	PQNType pCurrent = pq->_phead;
	PQNType pNext = NULL;
	while (pCurrent)
	{
		pNext = pCurrent->_next;
		free(pCurrent);
		pCurrent = pNext;
	}
	pq->_phead = NULL;
	pq->_ptail = NULL;
	pq->_size = 0;
	free(pq);
}

static PQNType BuyNode(QDataType val)
{
	PQNType p = (PQNType)malloc(sizeof(QNType));
	if (p == NULL)
	{
		perror("BuyNode malloc fail");
		return NULL;
	}
	p->_data = val;
	p->_next = NULL;
	return p;
}

void QPush(PQType pq, QDataType val)
{
	assert(pq);
	PQNType newNode = BuyNode(val);
	pq->_ptail->_next = newNode;
	pq->_ptail = newNode;
	pq->_size++;
}

int QSize(PQType pq)
{
	assert(pq);
	return pq->_size;
}

void QPop(PQType pq)
{
	assert(pq);
	if (QSize(pq) > 0)
	{
		if (pq->_phead->_next == pq->_ptail)
		{
			PQNType second = pq->_phead->_next->_next;
			free(pq->_phead->_next);
			pq->_phead->_next = second;
			pq->_size--;
			pq->_ptail = pq->_phead;
			return;
		}
		else
		{
			PQNType second = pq->_phead->_next->_next;
			free(pq->_phead->_next);
			pq->_phead->_next = second;
			pq->_size--;
			return;
		}
	}
	else
	{
		printf("The queue already null!\n");
		return;
	}
}

QDataType QReadFront(PQType pq)
{
	assert(pq);
	assert(QSize(pq) > 0); 
	return pq->_phead->_next->_data;
}

QDataType QReadBack(PQType pq)
{
	assert(pq);
	assert(QSize(pq) > 0);
	return pq->_ptail->_data;
}
```

```c
//Test.c
void test2()
{
	PQType pq = QInit();
	QPush(pq, 1);
	QPush(pq, 2);
	QPush(pq, 3);
	QPop(pq);
	QPop(pq);
	QPop(pq);
	QPush(pq, 1);
	QPush(pq, 2);
	QPush(pq, 3);
	QDataType x = QReadFront(pq);
	printf("%d\n", x);
	x = QReadBack(pq);
	printf("%d\n", x);
	QDestory(pq);
	pq = NULL;
}
```

这里通过带头单向不循环链表实现了队列。入队底层是链表尾插，出队底层是链表头删。为了在入队时不用再遍历链表找到尾节点，我们会记录尾节点，不过这样做也有一定风险，当最后一个存储有效数据的节点被删除后，`_ptail`就成了野指针，所以要留意一下，当删除最后一个有效数据节点时，将`_ptail`回滚到哨兵位。至于为什么会有队尾队头读取，这主要是跟着C++标准走的。

目前测试结果正常。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408121253702.mp4"></video>

