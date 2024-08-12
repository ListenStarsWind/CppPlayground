# [用两个栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/description/)

![image-20240812172625919](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408121726242.png)

刚刚才写过《用队列实现栈》，此处的主体思路相似，但有些细节可以更改，在一个栈里插入1234，再把这些数据插入到另一个栈里，就会发现此时出栈顺序就是1234，即实现了队列的先进先出，这是因为栈的性质是先进后出，所以再重新插入到新的栈之后，其出栈顺序刚好和原先的入栈顺序相同。所以我们不必要像《用队列实现栈》，每次弹出都要把栈倒出来倒出去，如果这样做的话，反而会出现错误的效果。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408121748413.mp4"></video>

```c
typedef int STDataType;
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

void STPopAll(PST stack) {
    assert(stack);
    while (STSize(stack)) {
        STDataType val = STPop(stack);
        printf("%d--", val);
    }
    printf("NULL\n");
}

STDataType STReadTop(PST stack) {
    assert(stack);
    return stack->_val[stack->_top - 1];
}

typedef struct {
    PST _pushStack;
    PST _popStack;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* pq = (MyQueue*)malloc(sizeof(MyQueue));
    if (pq == NULL) {
        perror("myQueueCreate malloc fail");
        return NULL;
    }
    pq->_pushStack = STInit();
    pq->_popStack = STInit();
    return pq;
}

void myQueuePush(MyQueue* obj, int x) { STPush(obj->_pushStack, x); }

int myQueuePop(MyQueue* obj) {
    if (STEmpty(obj->_popStack)) {
        while (!STEmpty(obj->_pushStack)) {
            STPush(obj->_popStack, STPop(obj->_pushStack));
        }
    }
    return STPop(obj->_popStack);
}

int myQueuePeek(MyQueue* obj) {
    if (STEmpty(obj->_popStack)) {
        while (!STEmpty(obj->_pushStack)) {
            STPush(obj->_popStack, STPop(obj->_pushStack));
        }
    }
    return STReadTop(obj->_popStack);
}

bool myQueueEmpty(MyQueue* obj) {
    if (STEmpty(obj->_pushStack) && STEmpty(obj->_popStack)) {
        return true;
    } else {
        return false;
    }
}

void myQueueFree(MyQueue* obj) {
    STDestroy(obj->_pushStack);
    STDestroy(obj->_popStack);
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/
```

