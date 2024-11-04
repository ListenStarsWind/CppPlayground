
//Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
 

#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
        queue<TreeNode*> q;
        int leveles = 0;
        if (root) {
            q.push(root);
            leveles = q.size();
        }

        while (!q.empty()) {
            vector<int> v;
            while (leveles--) {
                TreeNode* current = q.front();
                q.pop();

                v.push_back(current->val);

                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            vv.push_back(v);
            v.clear();
            leveles = q.size();
        }
        return vv;
    }
};