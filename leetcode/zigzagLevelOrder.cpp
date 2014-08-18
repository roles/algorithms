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
        vector<vector<int> > ret;
        vector<int> vis;

        vector<vector<int> > zigzagLevelOrder(TreeNode *root){
            ret.clear();
            vis.clear();

            if(!root)
                return ret;
            queue<TreeNode*> q;
            q.push(root);
            bool r = false;
            int layerNode = 1, nextLayerNode = 0, curNode = 0;
            while(!q.empty()){
                TreeNode *u = q.front();
                q.pop();
                vis.push_back(u->val);

                if(u->left){
                    q.push(u->left);
                    nextLayerNode++;
                }
                if(u->right){
                    q.push(u->right);
                    nextLayerNode++;
                }

                if(curNode == layerNode-1){
                    layerNode = nextLayerNode;
                    nextLayerNode = 0;
                    curNode = 0;
                    if(r){
                        reverse(vis.begin(), vis.end());    
                    }
                    ret.push_back(vis);
                    r = !r;
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

    vector<vector<int> > ret = s.zigzagLevelOrder(a);
    for(auto& vec : ret){
        for(auto x : vec){
            cout << x << '\t';
        }
        cout << endl;
    }
    return 0;
}
