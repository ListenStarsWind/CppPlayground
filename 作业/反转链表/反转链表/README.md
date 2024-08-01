# [反转链表](https://leetcode.cn/problems/reverse-linked-list/description/)

![image-20240730112643850](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407301126045.png)

这个之前也写过。不过看上去像是暴力破解。现在看上去挺简单，现在的解决方案是遍历每个节点，记录它的上一个和下一个节点，然后让当前节点的指针域指向上一个节点就行了。

算法二：

依次读取原链表的节点，把节点头插到一个新的链表，最后返回这个新链表。

```c
typedef struct ListNode* PListNode;

struct ListNode* reverseList(struct ListNode* head) {
    PListNode destination = NULL;
    PListNode source = head;
    PListNode terminal = NULL;
    while (source) {
        destination = source;
        source = source->next;
        destination->next = terminal;
        terminal = destination;
    }
    return destination;
}
```

