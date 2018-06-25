#include<iostream>
#include"tree_head.h"

TreeNode* ReverseTree(TreeNode* root) {
    if (!root) {
        return root;
    }
    
    TreeNode* tmp = root->left;
    root->left = root->right;
    root->right = tmp; 

    ReverseTree(root->left);
    ReverseTree(root->right);

    return root;
}

int main() {
    TreeNode* root;
	BuildTree(root);

    PrintTree(root);
	ReverseTree(root);
    PrintTree(root);
	return -1;
}
