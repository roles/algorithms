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
        bool _isBalanced(TreeNode *root, int &h){
            int left = 0, right = 0;
            if(root->left && !_isBalanced(root->left, left))
                return false;
            if(root->right && !_isBalanced(root->right, right))
                return false;
            if(abs(left - right) > 1){
                return false;
            }else{
                h = max(left, right) + 1;
                return true;
            }
        }

        bool isBalanced(TreeNode *root){
            if(!root)
                return true;
            int h;
            return _isBalanced(root, h);
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
    c->right = e;

    TreeNode *f = new TreeNode(6);
    //TreeNode *g = new TreeNode(7);
    d->left = f;
    //d->right = g;

    cout << s.isBalanced(a) << endl;

    return 0;
}
