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
        TreeNode* copyTree(TreeNode *root){
            if(!root)
                return NULL;
            TreeNode* newRoot = new TreeNode(root->val); 
            newRoot->left = copyTree(root->left);
            newRoot->right = copyTree(root->right);
            return newRoot;
        }

        void deleteTree(TreeNode *root){
            if(!root)
                return;
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }

        vector<TreeNode*> _generateTrees(int b, int e){
            vector<TreeNode*> ret, left, right;
            for(int i = b; i <= e; i++){
                left.clear();
                right.clear();
                TreeNode* root = new TreeNode(i);
                if(i != b){
                    left = _generateTrees(b, i-1);
                }
                if(i != e){
                    right = _generateTrees(i+1, e);
                }
                for(int p = 0; p < max(1, int(left.size())); p++){
                    for(int q = 0; q < max(1, int(right.size())); q++){
                        if(left.size() != 0){
                            root->left = copyTree(left[p]);
                        }
                        if(right.size() != 0){
                            root->right = copyTree(right[q]);
                        }
                        ret.push_back(root);
                    }
                }
                for(int p = 0; p < left.size(); p++){
                    deleteTree(left[p]);
                }
                for(int q = 0; q < right.size(); q++){
                    deleteTree(right[q]);
                }
            }
            return ret;
        }

        vector<TreeNode*> generateTrees(int n){
            if(n == 0)
                return vector<TreeNode*>{NULL};
            return _generateTrees(1, n);
        }
};

int main(){
    Solution s; 
    s.generateTrees(4);
    return 0;
}
