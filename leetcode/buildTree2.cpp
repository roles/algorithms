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

    TreeNode* _buildTree(iIter in_begin, iIter in_end,
            iIter post_begin, iIter post_end){
        TreeNode *root = new TreeNode(*(post_end-1));
        if(post_begin+1 == post_end)
            return root;
        iIter in_root = find(in_begin, in_end, *(post_end-1)); 
        if(in_root != in_begin){
            root->left = _buildTree(in_begin, in_root, post_begin, post_begin+(in_root-in_begin));
        }
        if(in_root != in_end-1){
            root->right = _buildTree(in_root+1, in_end, post_begin+(in_root-in_begin), post_end-1);
        }
        return root;
    }

    TreeNode* buildTree(vector<int> &inorder, vector<int> &postorder) {
        if(!inorder.size() || !postorder.size())
            return NULL;
        return _buildTree(inorder.begin(), inorder.end(), 
                postorder.begin(), postorder.end());
    }
};

void print_preorder(TreeNode *root){
    if(root == NULL)
        return;
    cout << root->val;
    print_preorder(root->left);
    print_preorder(root->right);
}

int main(){
    Solution s;
    vector<int> inorder{2,1}, postorder{2,1};
    //vector<int> preorder{1,2,3}, inorder{3,2,1};
    TreeNode* t = s.buildTree(inorder, postorder);
    print_preorder(t);
    cout << endl;
    return 0;
}
