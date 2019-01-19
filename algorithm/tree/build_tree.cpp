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

TreeNode* RebuildTree(string input, int& index) {

    cout << "id:" << index << " str:" <<  input[index] <<endl;
    if (input[index] == '#' ) {
        return NULL;
    }
    
    TreeNode* new_root = new TreeNode(int(input[index]) - 48 );
    index = index +1;
    TreeNode* left_child = RebuildTree(input, index);
    index = index +1;
    TreeNode* right_child = RebuildTree(input, index);
    new_root->left = left_child;
    new_root->right = right_child;
    return new_root;
}

int main() {
    TreeNode* root;
	BuildTree(root);
    PrintTree(root);

    TreeNode* new_root = CopyTree(root);
    PrintTree(new_root);

    int index = 0;
    TreeNode* new_root2 = RebuildTree("12##3##", index); 
    PrintTree(new_root2);
    return -1;	
}
