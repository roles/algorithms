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
        bool _isSameTree(TreeNode *left, TreeNode *right){
            if(left->val != right->val){
                return false;
            }
            bool leftSym, rightSym;
            if(left->left && !right->left || !left->left && right->left){
                return false;
            }else if(!left->left && !right->left){
                leftSym = true;
            }else{
                leftSym = _isSameTree(left->left, right->left);
            }

            if(left->right && !right->right || !left->right && right->right){
                return false;
            }else if(!left->right && !right->right){
                rightSym = true;
            }else{
                rightSym = _isSameTree(left->right, right->right);
            }

            return (leftSym && rightSym);
        }

        bool isSameTree(TreeNode *left, TreeNode *right){
            if(!left && !right)
                return true;
            if(!left || !right)
                return false;
            return _isSameTree(left, right);
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

    return 0;
}
