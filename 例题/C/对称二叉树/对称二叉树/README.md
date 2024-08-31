# 对称二叉树

![image-20240828104401076](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408281044451.png)

这个思路也比较简单：这其实就是看左右两棵子树是否镜像对称。什么叫做镜像对称？就是左右子树的根节点要相等，左子树的左子树要和右子树的右子树对称 并且 左子树的右子树要和右子树的左子树对称。

这样的话，原先的接口就不太适用了，按照上面的思路，接口应该是左右子树，所以要再写个子函数。子函数的名字一般是原函数的名字前面再加下划线。这样做的另一个好处是可以把无法重复的部分写在原函数里，重复的部分写在子函数里。

```c
bool _isSymmetric(struct TreeNode* LeftRoot, struct TreeNode* RightRood) {
    if (LeftRoot == NULL && RightRood == NULL)
        return true;
    if (LeftRoot == NULL || RightRood == NULL)
        return false;
    if (LeftRoot->val != RightRood->val)
        return false;
    return _isSymmetric(LeftRoot->left, RightRood->right) &&
           _isSymmetric(LeftRoot->right, RightRood->left);
}

bool isSymmetric(struct TreeNode* root) {
    assert(root);
    return _isSymmetric(root->left, root->right);
}
```

# 完