#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL) , next(NULL) {}
};

class Solution {
    public:
        void connect(TreeLinkNode *root){
            if(root == NULL)
                return;
            int layerNode = 1, curNode = 0, nextLayerNode = 0;
            queue<TreeLinkNode*> q;
            q.push(root);
            TreeLinkNode *pre = root;
            while(!q.empty()){
                TreeLinkNode *u = q.front();
                q.pop();
                if(u->left != NULL){
                    q.push(u->left);
                    nextLayerNode++;
                }
                if(u->right != NULL){
                    q.push(u->right);
                    nextLayerNode++;
                }

                if(curNode == 0){
                    pre->next = NULL;
                }else{
                    pre->next = u;
                }
                pre = u;

                if(curNode == layerNode-1){
                    layerNode = nextLayerNode;
                    curNode = 0;
                    nextLayerNode = 0;
                }else{
                    curNode++;
                }
            }
            pre->next = NULL;
        }
};

int main(){
    Solution s; 
    TreeLinkNode *a = new TreeLinkNode(1); 
    TreeLinkNode *b = new TreeLinkNode(2);
    TreeLinkNode *c = new TreeLinkNode(3); 
    a->left = b;
    a->right = c;

    TreeLinkNode *d = new TreeLinkNode(4);
    TreeLinkNode *e = new TreeLinkNode(5);
    b->left = d;
    b->right = e;

    TreeLinkNode *f = new TreeLinkNode(6);
    TreeLinkNode *g = new TreeLinkNode(7);
    c->left = f;
    c->right = g;

    s.connect(a);
    return 0;
}
