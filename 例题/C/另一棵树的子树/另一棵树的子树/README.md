# 另一棵树的子树

![image-20240828134409266](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281344507.png)

其实就是看树1与树2是否相同，不相同，就看树1的左右子树与树2是否相同，仅此而已。

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

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (root == NULL)
        return false;
    if (isSameTree(root, subRoot))
        return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}
```

# 完