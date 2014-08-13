#include <iostream>
#include <vector>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        void _preorder(vector<int> &preorder, TreeNode *root){
            if(root == NULL){
                return;
            }else{
                preorder.push_back(root->val);
                _preorder(preorder, root->left); 
                _preorder(preorder, root->right); 
            }
        }

        vector<int> preorderTraversal(TreeNode *root) {
            vector<int> ret;
            _preorder(ret, root);
            return ret;
        }
};

int main(){
    Solution s; 
     
    return 0;
}
