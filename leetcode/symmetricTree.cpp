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
        bool _isSymmetric(TreeNode *left, TreeNode *right){
            if(left->val != right->val){
                return false;
            }
            bool leftSym, rightSym;
            if(left->left && !right->right || !left->left && right->right){
                return false;
            }else if(!left->left && !right->right){
                leftSym = true;
            }else{
                leftSym = _isSymmetric(left->left, right->right);
            }

            if(left->right && !right->left || !left->right && right->left){
                return false;
            }else if(!left->right && !right->left){
                rightSym = true;
            }else{
                rightSym = _isSymmetric(left->right, right->left);
            }

            return (leftSym && rightSym);
        }

        bool isSymmetric(TreeNode *root){
            if(!root)
                return true;
            if(!root->left && !root->right)
                return true;
            if(!root->left || !root->right)
                return false;
            return _isSymmetric(root->left, root->right);
        }
};

int main(){
    Solution s; 
    TreeNode *a = new TreeNode(1); 
    TreeNode *b = new TreeNode(2);
    TreeNode *c = new TreeNode(2); 
    a->left = b;
    a->right = c;

    TreeNode *d = new TreeNode(3);
    TreeNode *e = new TreeNode(4);
    b->left = d;
    b->right = e;

    TreeNode *f = new TreeNode(4);
    TreeNode *g = new TreeNode(3);
    c->left = f;
    c->right = g;

    cout << s.isSymmetric(a) << endl;
    return 0;
}
