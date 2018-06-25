#include<iostream>
#include"tree_head.h"

using namespace std;

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

bool JudgeTree(TreeNode* root, TreeNode* other) {
    if (!root || !other) {
        return root == other ? true: false ;
    }
    
    if (root->value == other->value) {
        bool flag_left = JudgeTree(root->left, other->right);
        bool flag_right = JudgeTree(root->right, other->left);
        return flag_left && flag_right;
    } 
    return false;
}

bool AddTree(TreeNode* root, TreeNode* other) {
    if (!root || !other) {
        return root == other ? true: false ;
    }
    
    if (root->value == other->value) {
        bool flag_left = JudgeTree(root->left, other->right);
        bool flag_right = JudgeTree(root->right, other->left);
        return flag_left && flag_right;
    } 
    return false;
}

int main() {
    TreeNode* root;
	BuildTree(root);
    PrintTree(root);
	ReverseTree(root);
    PrintTree(root);

    bool flag = JudgeTree(root, root);
    cout << "flag:" << flag << endl;
	return -1;
}
