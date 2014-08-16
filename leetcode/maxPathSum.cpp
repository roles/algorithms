#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        //pathSum记录经过节点的单边最大
        //nodeSum记录该节点构成左右两边的最大值
        unordered_map<TreeNode*, int> pathSum, nodeSum;

        //返回pathSum
        int dfs(TreeNode *root){
            int left = 0, right = 0;
            if(root->left != NULL){
                left = dfs(root->left);
            }
            if(root->right != NULL){
                right = dfs(root->right);
            }
            int p = max(left, right);
            p = max(p, 0);
            p += root->val;
            pathSum[root] = p;

            int n = root->val;
            n += left > 0 ? left : 0;
            n += right > 0 ? right : 0;
            nodeSum[root] = n;

            return p;
        }

        int dfsMax(TreeNode* root){
            int maxVal = nodeSum[root];
            if(root->left != NULL){
                int left = dfsMax(root->left);
                if(left > maxVal){
                    maxVal = left;
                }
            }
            if(root->right != NULL){
                int right = dfsMax(root->right);
                if(right > maxVal){
                    maxVal = right;
                }
            }
            return maxVal;
        }

        int maxPathSum(TreeNode *root){
            if(root == NULL)
                return 0;
            pathSum.clear();
            nodeSum.clear();

            dfs(root);
            return dfsMax(root);
        }
};

int main(){
    Solution s; 
    TreeNode *a = new TreeNode(1); 
    TreeNode *b = new TreeNode(-1);
    TreeNode *c = new TreeNode(10); 
    a->left = b;
    a->right = c;

    TreeNode *d = new TreeNode(3);
    TreeNode *e = new TreeNode(9);
    b->left = d;
    b->right = e;

    TreeNode *f = new TreeNode(7);
    TreeNode *g = new TreeNode(4);
    d->left = f;
    d->right = g;

    cout << s.maxPathSum(a) << endl;
    return 0;
}
