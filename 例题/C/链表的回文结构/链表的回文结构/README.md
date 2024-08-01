# 链表的回文结构

什么是链表的回文结构呢？就是链表中存储的有效数据是镜面对称的，我也不知道这“回文”是怎么取出来的，“镜像”不更容易理解吗。不过这样空泛的说，似乎还不够形象。举个例子，现在有个链表，其内部存储的数据是这样的：[1,2,2,1]，这种链表就是“回文”的，这是偶数个节点，当有奇数个节点时，如[1,2,3,2,1]，这样也是“回文的”。

如何判断一个单链表是“回文的”呢？

- 先找到这个单链表的中间节点。对于[1,2,2,1]，中间节点是第二个[2]；对于[1,2,3,2,1]，中间节点就是[3]
- 从中间节点开始，逆置后面的节点，于是[2,1]被逆置成了[1,2]；[3,1,2]被逆置成了[1,2,3]
- 将逆置后的链表与中间节点前的链表节点逐个比对，都相等就是回文

循环变量就是逆置链表的遍历节点。当链表节点个数为奇数后，如[1,2,3,2,1]，前面链表[1,2]和逆置后的链表1,2,3]长度并不一致，但这不会引发`bug`，因为前链表[1,2]中的节点[2]的`next`在逆置时并没有被修改，也就是说，[2]的`next`仍旧指向[3]，所以仍然可以正常运行。

来看[这题](https://www.nowcoder.com/share/jump/9209693051722493771119)。

![image-20240801143004776](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408011430088.png)

这里没C，没有关系。我们使用C++，C是C++的一部分，把它当C写就行，把其它函数放在`class PalindromeList { public: };`冒号（:）和大括号（{};）之间就行。

找中间节点，逆置这两天刚写过，就直接`Ctrl + C  Ctrl + V`了。

```c++
#include<stdlib.h>

struct ListNode
{
    int val;
    struct ListNode* next;
};

class PalindromeList {
public:

    struct ListNode* middleNode(struct ListNode* head) {
        struct ListNode* PFast = head;
        struct ListNode* PSlow = head;
        while (PFast && PFast->next) {
            PFast = PFast->next->next;
            PSlow = PSlow->next;
        }
        return PSlow;
    }

    struct ListNode* reverseList(struct ListNode* head) {
        struct ListNode* PLast = NULL;
        struct ListNode* PCurrent = head;
        struct ListNode* PNext = head;
        while (PCurrent) {
            PNext = PCurrent->next;
            PCurrent->next = PLast;
            PLast = PCurrent;
            PCurrent = PNext;
        }
        return PLast;
    }

    bool chkPalindrome(ListNode* A) {
        // write code here
        struct ListNode* mind = middleNode(A);
        struct ListNode* rmind = reverseList(mind);
        while (rmind) {
            if (rmind->val != A->val) {
                return false;
            }
            else {
                rmind = rmind->next;
                A = A->next;
            }
        }
        return true;
    }
};
```

# 完

