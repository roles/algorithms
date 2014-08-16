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
        vector<vector<int> > ret;
        vector<int> vis;

        void _pathSum(TreeNode *root, int sum){
            if(root->val == sum && !root->left && !root->right){
                vis.push_back(root->val);
                ret.push_back(vis);
                vis.pop_back();
                return;
            }
            if(root->left){
                vis.push_back(root->val);
                _pathSum(root->left, sum-root->val);
                vis.pop_back();
            }
            if(root->right){
                vis.push_back(root->val);
                _pathSum(root->right, sum-root->val);
                vis.pop_back();
            }
        }

        vector<vector<int> > pathSum(TreeNode *root, int sum){
            ret.clear();
            vis.clear();

            if(!root)
                return ret;
            _pathSum(root, sum);
            return ret;
        }
};

int main(){
    Solution s; 
    TreeNode *a = new TreeNode(1); 
    TreeNode *b = new TreeNode(2);
    TreeNode *c = new TreeNode(5); 
    a->left = b;
    a->right = c;

    TreeNode *d = new TreeNode(3);
    TreeNode *e = new TreeNode(4);
    b->left = d;
    b->right = e;

    TreeNode *f = new TreeNode(6);
    TreeNode *g = new TreeNode(7);
    d->left = f;
    d->right = g;

    return 0;
}
