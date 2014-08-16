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
        TreeNode* _flatten(TreeNode* root){
            TreeNode* oriRight = root->right;
            TreeNode* last = root;
            if(root->left != NULL){
                root->right = root->left;
                last = _flatten(root->left); 
            }
            last->right = oriRight;
            root->left = NULL;

            if(oriRight != NULL){
                last = _flatten(oriRight);
            }
            return last;
        }

        void flatten(TreeNode *root){
            if(root == NULL)
                return;
            _flatten(root);
        }
};

int main(){
    Solution s; 
    /*
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
    c->right = f;
    */
    TreeNode *a = new TreeNode(1); 
    TreeNode *b = new TreeNode(2);
    a->left = b;

    s.flatten(a);

    TreeNode* cur = a;
    while(cur != NULL){
        cout << cur->val << '\t';
        cur = cur->right;
    }
    cout << endl;


    return 0;
}
