#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        int dfs(TreeNode* root, int curVal){
            int sum = 0;
            if(root->left != NULL){
                sum += dfs(root->left, curVal*10+root->val); 
            }
            if(root->right != NULL){
                sum += dfs(root->right, curVal*10+root->val);
            }
            if(root->left == NULL && root->right == NULL){
                return curVal*10+root->val; 
            }
            return sum;
        }

        int sumNumbers(TreeNode *root) {
            if(root == NULL)
                return 0;
            return dfs(root, 0);
        }
};

int main(){
    Solution s; 
    
    return 0;
}
