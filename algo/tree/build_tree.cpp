#include<iostream>
#include"tree_head.h"

using namespace std;

TreeNode* CopyTree(TreeNode* root) {
    if(!root) {
        return root;
    }
    
    TreeNode* new_root = new TreeNode(root->value);
    TreeNode* left_tree = CopyTree(root->left);
    TreeNode* right_tree = CopyTree(root->right);

    new_root -> left = left_tree;
    new_root -> right = right_tree;
    return new_root;
}

int main() {
    TreeNode* root;
	BuildTree(root);
    PrintTree(root);

    TreeNode* new_root = CopyTree(root);
    PrintTree(new_root);

    return -1;	
}
