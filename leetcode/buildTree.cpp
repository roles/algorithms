#include <iostream>
#include <vector>
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
    typedef vector<int>::iterator iIter;

    TreeNode* _buildTree(iIter pre_begin, iIter pre_end,
            iIter in_begin, iIter in_end){
        TreeNode *root = new TreeNode(*pre_begin);
        if(pre_begin+1 == pre_end)
            return root;
        iIter in_root = find(in_begin, in_end, *pre_begin); 
        if(in_root != in_begin){
            root->left = _buildTree(pre_begin+1, pre_begin+(in_root-in_begin)+1,
                    in_begin, in_root);
        }
        if(in_root != in_end-1){
            root->right = _buildTree(pre_begin+(in_root-in_begin)+1, pre_end,
                    in_root+1, in_end);
        }
        return root;
    }

    TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder) {
        if(!preorder.size() || !inorder.size())
            return NULL;
        return _buildTree(preorder.begin(), preorder.end(), 
                inorder.begin(), inorder.end());
    }
};

void print_postorder(TreeNode *root){
    if(root == NULL)
        return;
    print_postorder(root->left);
    print_postorder(root->right);
    cout << root->val;
}

int main(){
    Solution s;
    vector<int> preorder{1,2,4,6,7,3,5}, inorder{2,6,4,7,1,5,3};
    //vector<int> preorder{1,2,3}, inorder{3,2,1};
    TreeNode* t = s.buildTree(preorder, inorder);
    print_postorder(t);
    cout << endl;
    return 0;
}
