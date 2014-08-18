#include <iostream>
#include <vector>
#include <queue>
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
        int maxDepth(TreeNode *root){
            if(!root)
                return 0;
            queue<TreeNode*> q;
            q.push(root);
            int layerNode = 1, nextlayerNode = 0, layer = 0, curNode = 0;
            while(!q.empty()){
                TreeNode* u = q.front();
                q.pop();
                
                if(u->left){
                    q.push(u->left);
                    nextlayerNode++;
                }
                if(u->right){
                    q.push(u->right);
                    nextlayerNode++;
                }

                if(curNode == layerNode-1){
                    layer++;
                    layerNode = nextlayerNode;
                    nextlayerNode = 0;
                    curNode = 0;
                }else{
                    curNode++;
                }
            }
            return layer;
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

    cout << s.maxDepth(a) << endl;
    return 0;
}
