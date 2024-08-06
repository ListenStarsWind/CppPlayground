# [判断环形链表](https://leetcode.cn/problems/linked-list-cycle/description/)

![image-20240802120518383](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408021205622.png)

最开始，还真没什么思路。后来学到，这还是要用快慢指针来解决。用个形象但很不严谨的比喻，环形链表就像是一个钟表，开始时，钟表的时针和分针并不重合，但经过一定时间后它们就会重合。之所以说这种比喻是不严谨的，是因为钟表的指针是连续转的，而C里的指针是某一单位变化，并不连续。

```c
bool hasCycle(struct ListNode* head) {
    struct ListNode* Fast = head;
    struct ListNode* Slow = head;
    while (Fast && Fast->next) {
        Fast = Fast->next->next;
        Slow = Slow->next;
        if (Fast == Slow) {
            return true;
        }
    }
    return false;
}
```

证明如下：

现有一环形链表，其节点个数为N。为便于表述，下文将这N个节点依次编号为[0,1,2,3,4,……,N-2,N-1]。有两个指针`Fast`和`Slow`指向该环形链表中的节点。初始时，指针`Slow`指向0号节点，指针`Fast`指向D号节点。已知，指针`Fast`的移动速度为`F`个节点每次，指针`Slow`的移动速度为`S`个节点每次。试问，若要使这两个指针经过一定次数后必定相遇，对上述参数有何要求。

在转动K次后，指针`Fast`和指针`Slow`指向节点的编号可用下述表达式表述
$$
Fast(K) = D+K*F \mod N \\
Slow(K) = K*S \mod N
$$
当两个指针指向同一节点时，有
$$
Fast(K) = Slow(K) \mod N\\
D+K*F= K*S \mod N\\
$$
化简有
$$
K = \frac{D}{S-F}-MN  （M∈Z）
$$
其中$M$是一个整数，用于将$K$限制在0到N-1之间

由题意得，$K$是一个正整数，为了让$K$有解，$S-F$就必须是$D$的因式。

对于上面的代码来说，$S=1$，$F=2$，则$S-F=-1$，所以$S-F$一定是$D$的因数。故最终一定能够相遇。所以理论上说，$S=3$，$F=4$，也可以，但如果链表没有成环，而循环条件又没注意，就容易出现空指针解引用问题。

另外要注意，上述证明并不全面，因为如果链表成环的话，很明显，$D$不是任意的，它其实上还受到$S$和$F$的影响，而上述证明并没有考虑到这一点，不过由于-1是所有整数的因数，所以并不用考虑$D$到底是多少。