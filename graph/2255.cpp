#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct node {
    char val;
    node *left, *right;
};

string preorder, inorder;

node* recon_tree(int preorder_begin, int preorder_end,
                 int inorder_begin, int inorder_end){ 
    node* root = new node;
    int root_idx;

    if(preorder_begin > preorder_end){
        return NULL;
    }

    if(preorder_begin == preorder_end){
        root->val = preorder[preorder_begin];
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    root->val = preorder[preorder_begin];
    for(root_idx = inorder_begin; inorder[root_idx] != root->val; root_idx++);
 
    root->left = recon_tree(preorder_begin + 1 , preorder_begin + root_idx - inorder_begin, 
            inorder_begin, root_idx - 1);
    root->right = recon_tree(preorder_begin + root_idx - inorder_begin + 1, preorder_end,
            root_idx + 1, inorder_end);

    return root;
}

void print_postorder(node* root){
    if(root == NULL)
        return;
    print_postorder(root->left);
    print_postorder(root->right);
    cout << root->val;
}

void delete_tree(node* root){
    if(root == NULL)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

int main(){
    while(cin >> preorder >> inorder){
        node* root = recon_tree(0, preorder.size() - 1, 0, inorder.size() - 1); 
        print_postorder(root);
        cout << endl;
        delete_tree(root);
    }
    return 0;
}
