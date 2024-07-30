# [移除链表中的指定节点](https://leetcode.cn/problems/remove-linked-list-elements/description/)

![image-20240730115717482](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407301157693.png)

之前也写过，只不过看上去像是暴力破解。还是很简单，逐个对比，不相等的留下，相等的释放。

简单个屁，我改了很多次才提交成功。最起码改了几个小时，另外，在`VS`上我也专门搭建了测试开发模块 。为此，下面将对代码进行详细分析。

```c
typedef struct ListNode ListNode;

struct ListNode* removeElements(struct ListNode* head, int val) {
    PListNode PNewHead = head;
    PListNode PLast = NULL;
    PListNode PCurrent = NULL;
    PListNode PNext = NULL;
    while (head && head->val == val) {
        PNewHead = head->next;
        free(head);
        head = PNewHead;
    }
    if (PNewHead) {
        PLast = PNewHead;
        PCurrent = PNewHead->next;
    }
    while (PCurrent) {
        PNext = PCurrent->next;
        if (PCurrent->val != val) {
            PLast = PCurrent;
        }
        else {
            PLast->next = PNext;
            free(PCurrent);
        }
        PCurrent = PNext;
    }
    return PNewHead;
}
```

在最开始时，由于我刚刚写完项目《反转链表》，所以我一上来就仿照《反转链表》创建并初始化了三个指针。

```c
PListNode PLast = NULL;
PListNode PCurrent = head;
PListNode PNext = head;
```

然后我就赶紧写第二个循环了，也就是`while (PCurrent)`部分。

```c
while (PCurrent) {
    PNext = PCurrent->next;
    if (PCurrent->val != val) {
        PLast = PCurrent;
    }
    else {
        PLast->next = PNext;
        PLast = PCurrent;
        free(PCurrent);
    }
    PCurrent = PNext;
}
```

写完之后，我就扫了一眼，然后就想到了一个问题：“要是第一个节点就和val相等怎么办？那样不就不能直接返回head了吗。”，于是我赶紧又创建了一个指针：`PListNode PNewHead = NULL;`。我的想法是，把第一个不和`val`相等的节点地址赋给`PNewHead`，为此我又创建了一个`flag`，`flag`初始值为1，它会成为一个`if`语句的判断条件，这个`if`语句内部将会把第一个非`val`的节点地址赋给`PNewHead`，然后再把`flag`变为假，从而确保这个`if`语句只会执行一次。大致是这样的：

```c
while (PCurrent) {
    PNext = PCurrent->next;
    if (PCurrent->val != val) {
        if(flag){
            PNewNode = PCrrent;
            PList = PNewNode;
            flag = 0;
        }
        PLast = PCurrent;
    }
    else {
        PLast->next = PNext;
        PLast = PCurrent;
        free(PCurrent);
    }
    PCurrent = PNext;
}
```

然后我又想到“万一第一个节点不和val相等，那就会对空指针`PLast`解引用，这怎么办？”于是我决定干脆在`while (PCurrent)`之前再弄个循环，这个循环的目的就是找到合法的（节点内部数值与val不相同的）首节点，找到之后再以这个首节点为基础，对上一个和当前指针初始化。既然`PCurrent`和`PCurrent`是在第一个循环和第二个循环之间初始化的，干脆创建的时候就初始化成空。

```c
while (head->val == val) {
    PNewHead = head->next;
    free(head);
    head = PNewHead;
}
PLast = PNewHead;
PCurrent = PNewHead;

while (PCurrent) {
    PNext = PCurrent->next;
    if (PCurrent->val != val) {
        PLast = PCurrent;
    }
    else {
        PLast->next = PNext;
        PLast = PCurrent;
        free(PCurrent);
    }
    PCurrent = PNext;
}
```

然后我又想到“万一这链表空了怎么办？”于是又改成了。

```c
while (head && head->val == val) {
    PNewHead = head->next;
    free(head);
    head = PNewHead;
}
PLast = PNewHead;
PCurrent = PNewHead;

while (PCurrent) {
    PNext = PCurrent->next;
    if (PCurrent->val != val) {
        PLast = PCurrent;
    }
    else {
        PLast->next = PNext;
        PLast = PCurrent;
        free(PCurrent);
    }
    PCurrent = PNext;
}
```

然后我发现这个代码还是不行，经过调试后我意识到这样写的话会让`PLast`和`PCurrent`在每次循环里都指向同一个节点，我最开始的解决方案是把这两个指针初始化过程挪到第二个循环里。

```c
while (head && head->val == val) {
    PNewHead = head->next;
    free(head);
    head = PNewHead;
}

while (PCurrent) {
    if(flag){
        PLast = PNewHead;
        PCurrent = PNewHead;
        flag = 0;
    }
    PNext = PCurrent->next;
    if (PCurrent->val != val) {
        PLast = PCurrent;
    }
    else {
        PLast->next = PNext;
        PLast = PCurrent;
        free(PCurrent);
    }
    PCurrent = PNext;
}
```

跑了之后，还是不行，原因是我刚刚把`PCurrent`创建时初始化成空了。于是我把这两个初始化又挪回了两个循环中间。为了让它俩初始化后不指向同一个节点，写成：

```c
while (head && head->val == val) {
    PNewHead = head->next;
    free(head);
    head = PNewHead;
}
PLast = PNewHead;
PCurrent = PNewHead->next;

while (PCurrent) {
    PNext = PCurrent->next;
    if (PCurrent->val != val) {
        PLast = PCurrent;
    }
    else {
        PLast->next = PNext;
        PLast = PCurrent;
        free(PCurrent);
    }
    PCurrent = PNext;
}
```

然后跑了，还是不行，因为链表存在空的可能，此时`PNewHead`为空，不能解引用。反正经过第一个循环之后，`PNewHead`一定是合法的，所以这样写：

```c
struct ListNode* removeElements(struct ListNode* head, int val) {
    PListNode PNewHead = head;
    PListNode PLast = NULL;
    PListNode PCurrent = NULL;
    PListNode PNext = NULL;
    while (head && head->val == val) {
        PNewHead = head->next;
        free(head);
        head = PNewHead;
    }
    if (PNewHead) {
        PLast = PNewHead;
        PCurrent = PNewHead->next;
    }
    while (PCurrent) {
        PNext = PCurrent->next;
        if (PCurrent->val != val) {
            PLast = PCurrent;
        }
        else {
            PLast->next = PNext;
            PLast = PCurrent;
            free(PCurrent);
        }
        PCurrent = PNext;
    }
    return PNewHead;
}
```

然后还是不行，因为当遇到非法的节点时，`PLast`会被释放掉，整个链表就会崩溃。既然两个分支都有`PLast = PCurrent;`，干脆就直接把它移到`PCurrent = PNext;`后：

```c
struct ListNode* removeElements(struct ListNode* head, int val) {
    PListNode PNewHead = head;
    PListNode PLast = NULL;
    PListNode PCurrent = NULL;
    PListNode PNext = NULL;
    while (head && head->val == val) {
        PNewHead = head->next;
        free(head);
        head = PNewHead;
    }
    if (PNewHead) {
        PLast = PNewHead;
        PCurrent = PNewHead->next;
    }
    while (PCurrent) {
        PNext = PCurrent->next;
        if (PCurrent->val != val) {
            ;
        }
        else {
            PLast->next = PNext;
           	free(PCurrent);
        }
        PCurrent = PNext;
        PLast = PCurrent;
    }
    return PNewHead;
}
```

还是不行，当遇到连续非法的节点时。比如对于`[1,2,2,1], val = 2`，经过第一循环和其后的两个初始化后，`PLast`指向（val为）1的节点，`PCurrent`指向第一个2的节点，在第一次循环之后，`PLast`指向第二个2的节点，然后在第二次循环之后，`PLast`就被释放掉了，链表崩溃。

```c
struct ListNode* removeElements(struct ListNode* head, int val) {
    PListNode PNewHead = head;
    PListNode PLast = NULL;
    PListNode PCurrent = NULL;
    PListNode PNext = NULL;
    while (head && head->val == val) {
        PNewHead = head->next;
        free(head);
        head = PNewHead;
    }
    if (PNewHead) {
        PLast = PNewHead;
        PCurrent = PNewHead->next;
    }
    while (PCurrent) {
        PNext = PCurrent->next;
        if (PCurrent->val != val) {
            PLast = PCurrent;
        }
        else {
            PLast->next = PNext;
            free(PCurrent);
        }
        PCurrent = PNext;
    }
    return PNewHead;
}
```

这次过去了，不过仍无法肯定该算法的正确性，目前仅确定该算法通过了力扣的全部测试用例。

