# [链表分割](https://www.nowcoder.com/share/jump/9209693051722416406869)

![image-20240731170156239](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407311701465.png)

怪了，它不支持`C`，只支持`C++ and C#`，用`C++`将就写。创建两个带头链表，一个存小于的节点，另一个存不小于的节点，最后连起来就行。

带有哨兵位：

```c++
class Partition {
  public:
    ListNode* partition(ListNode* pHead, int x) {
        // write code here
        struct ListNode* PHigh = (struct ListNode*)malloc(sizeof(struct ListNode));
        struct ListNode* PLow = (struct ListNode*)malloc(sizeof(struct ListNode));
        struct ListNode* TerminateH = PHigh;
        struct ListNode* TerminateL = PLow;
        struct ListNode* Current = pHead;
        while (Current) {
            if (Current->val < x) {
                TerminateL->next = Current;
                TerminateL = TerminateL->next;
            } else {
                TerminateH->next = Current;
                TerminateH = TerminateH->next;
            }
            Current = Current->next;
        }
        TerminateH->next = NULL;
        Current = PHigh->next;
        free(PHigh);
        PHigh = Current;
        TerminateL->next = PHigh;
        Current = PLow->next;
        free(PLow);
        PLow = Current;
        return PLow;
    }
};
```

不带哨兵位的就不逝世了。