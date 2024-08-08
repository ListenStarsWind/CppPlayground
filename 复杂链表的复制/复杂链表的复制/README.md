# [复杂链表的复制](https://leetcode.cn/problems/copy-list-with-random-pointer/description/)

![image-20240808114010385](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408081140584.png)

直接讲吧。算法的核心是构造一种机制，使得原链表节点与复制出的节点建立起一一对应的关系，以这个关系为桥梁复制出新的链表。

总共分为三个阶段。原链表如下：

![image-20240808125410150](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408081254222.png)

阶段一，遍历链表，创建新的节点，把新的节点插入原链表，插入位置是对应节点的后面。

![image-20240808125552300](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408081255372.png)

阶段二，依据对应关系，为新节点的`random`赋值。

![image-20240808125801397](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408081258458.png)

阶段三，将新节点从原链表中拆除，组成新的链表，并恢复原链表。

![image-20240808125924179](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408081259233.png)

代码如下，代码规模较大，细节较多，建议跟着图慢慢走。

```c
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node* copyRandomList(struct Node* head) {
    struct Node* source = head;
    struct Node* destination = NULL;
    struct Node* quondamNext = NULL;
    while (source) {
        quondamNext = source->next;
        destination = (struct Node*)malloc(sizeof(struct Node));
        if (destination == NULL) {
            printf("error:copy fail!\n");
            return NULL;
        }
        destination->next = quondamNext;
        destination->val = source->val;
        source->next = destination;
        source = quondamNext;
    }
    destination = NULL;

    struct Node* quondam = head;
    struct Node* copy = NULL;
    quondamNext = NULL;
    while (quondam) {
        copy = quondam->next;
        quondamNext = copy->next;
        if (quondam->random == NULL) {
            copy->random = NULL;
        } else {
            copy->random = quondam->random->next;
        }
        quondam = quondamNext;
    }

    struct Node* copyHead = NULL;
    struct Node* copyTrail = copyHead;
    quondam = head;
    copy = NULL;
    quondamNext = NULL;
    while (quondam) {
        copy = quondam->next;
        quondamNext = copy->next;
        quondam->next = quondamNext;
        if (quondam == head) {
            copyHead = copy;
            copyTrail = copyHead;
        } else {
            copyTrail->next = copy;
            copyTrail = copyTrail->next;
        }
        quondam = quondamNext;
    }

    return copyHead;
}
```

