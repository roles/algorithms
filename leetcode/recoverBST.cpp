#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
* 根据中序遍历来看哪两个位置错乱，非递归非栈的中序遍历如下
* Morris Traversal
* 1. Initialize current as root 
* 2. While current is not NULL
*    If current does not have left child
*        a) Print current’s data
*        b) Go to the right, i.e., current = current->right
*    Else
*        a) Make current as right child of the rightmost node in current's left subtree
*        b) Go to this left child, i.e., current = current->left
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        void recoverTree(TreeNode *root){
            TreeNode *p1 = NULL, *p2 = NULL, *cur = root, *pre = NULL;

            while(cur != NULL){
                if(!cur->left){
                    if(pre && pre->val > cur->val){
                        if(!p1){
                            p1 = pre;
                        }
                        p2 = cur;
                    }
                    pre = cur;
                    cur = cur->right;
                }else{
                    TreeNode *rightMost = cur->left;
                    while(rightMost->right != NULL && rightMost->right != cur)
                        rightMost = rightMost->right;
                    if(!rightMost->right){
                        rightMost->right = cur;
                        cur = cur->left;
                    }else{
                        if(pre && pre->val > cur->val){
                            if(!p1){
                                p1 = pre;
                            }
                            p2 = cur;
                        }
                        pre = cur;
                        rightMost->right = NULL;
                        cur = cur->right;
                    }
                }
            }

            int tmp = p1->val;
            p1->val = p2->val;
            p2->val = tmp;
        }
};

void print_inorder(TreeNode* root){
    if(!root)
        return;
    print_inorder(root->left);
    cout << root->val << '\t';
    print_inorder(root->right);
}

int main(){
    Solution s; 
    TreeNode *a = new TreeNode(9); 
    TreeNode *b = new TreeNode(13);
    TreeNode *c = new TreeNode(3); 
    a->left = b;
    a->right = c;

    TreeNode *d = new TreeNode(1);
    TreeNode *e = new TreeNode(5);
    b->left = d;
    b->right = e;

    TreeNode *f = new TreeNode(11);
    TreeNode *g = new TreeNode(17);
    c->left = f;
    c->right = g;

    print_inorder(a);
    cout << endl;

    s.recoverTree(a);
    print_inorder(a);
    cout << endl;

    return 0;
}
