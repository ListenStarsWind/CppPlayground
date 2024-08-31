# [单值二叉树](https://leetcode.cn/problems/univalued-binary-tree/description/)

![image-20240826135002578](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408261350779.png)

首先要知道什么是单值二叉树。

如果二叉树每个节点都具有相同的值，那么该二叉树就是单值二叉树。

思路也简单。“判断这棵树是否是单值二叉树”可以拆成“根节点与子节点数值是否相同”+“左右子树是否是单值二叉树”这两个子问题（应用的是等号的传递性）。对于一棵空树，它当然是单值二叉树；若根节点的数值与子节点数值相同，不能证明什么，但若是不相同，则可一锤定音，这肯定不是单值二叉树。

在实际比对过程中，为了防止子树为空，根节点与子节点比较之前需要先判断子树一定不为空，子树为空本身并不能证明什么，所以没有拆分成单独的if来写，而是用了逻辑与的短路属性。

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isUnivalTree(struct TreeNode* root) {
    if (root == NULL)
        return true;
    if (root->left && root->left->val != root->val)
        return false;
    if (root->right && root->right->val != root->val)
        return false;
    return isUnivalTree(root->left) && isUnivalTree(root->right);
}
```

# 完