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
        void _inorder(vector<int> &inorder, TreeNode *root){
            if(root == NULL){
                return;
            }else{
                _inorder(inorder, root->left); 
                inorder.push_back(root->val);
                _inorder(inorder, root->right); 
            }
        }

        vector<int> inorderTraversal(TreeNode *root) {
            vector<int> ret;
            _inorder(ret, root);
            return ret;
        }
};

int main(){
    Solution s; 
     
    return 0;
}
