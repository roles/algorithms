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
        TreeNode* _sortedArrayToBST(vector<int> &num, int start, int end){
            if(start == end){
                return NULL;
            }
            int mid = (start + end) / 2;
            TreeNode* node = new TreeNode(num[mid]);
            node->left = _sortedArrayToBST(num, start, mid);
            node->right = _sortedArrayToBST(num, mid+1, end);
            return node;
        }
        
        TreeNode *sortedArrayToBST(vector<int> &num) {
            return _sortedArrayToBST(num, 0, num.size());
        }
};

int main(){
    Solution s; 
    
    return 0;
}
