#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
        vector<vector<int> > levelOrder(TreeNode *root){
            vector<vector<int> > ret;
            vector<int> vis;
            if(root == NULL)
                return ret;
            int layerNode = 1, curNode = 0, nextLayerNode = 0;
            queue<TreeNode*> q;
            q.push(root);
            while(!q.empty()){
                TreeNode *u = q.front();
                vis.push_back(u->val);
                q.pop();
                if(u->left != NULL){
                    q.push(u->left);
                    nextLayerNode++;
                }
                if(u->right != NULL){
                    q.push(u->right);
                    nextLayerNode++;
                }

                if(curNode == layerNode-1){
                    layerNode = nextLayerNode;
                    curNode = 0;
                    nextLayerNode = 0;
                    ret.push_back(vis);
                    vis.clear();
                }else{
                    curNode++;
                }
            }
            return ret;
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

    vector<vector<int> > ret = s.levelOrderBottom(a);
    for(auto &vec : ret){
        for(auto x : vec){
            cout << x << '\t';
        }
        cout << endl;
    }
    return 0;
}
