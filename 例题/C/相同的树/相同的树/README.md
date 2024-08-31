# [相同的树](https://leetcode.cn/problems/same-tree/description/)

![image-20240826105517575](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261055885.png)

思路很简单，“两棵树相同”这个问题可以被拆分成“两棵树的对应左右子树相同”。接下来是设定边界条件。遍历次序是先序遍历。先判断根节点，根节点相同证明不了什么，不相同倒可以证明确实不相同。当然，在看根节点数值相同之前先要保证节点不为空，如果都为空，可以证明这两颗子树确实相同；若只有一个为空，则证明子树不相同。

```c
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL)
        return true;
    if (p == NULL || q == NULL)
        return false;
    if (p->val != q->val)
        return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
```



# 完