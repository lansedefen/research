#include<iostream>
#include"tree_head.h"

using namespace std;

TreeNode* tree2list(TreeNode* root) {
	if (root == NULL || (root->left == NULL && root-> right == NULL)) {
		return root;
	}

	TreeNode* left_head = tree2list(root->left);
	TreeNode* right_head = tree2list(root->right);
	if (left_head) {
		TreeNode* left_tail = left_head;
		while(left_tail->right) {
			left_tail = left_tail ->right;
		}
		left_tail -> right = root;
		root->left = left_tail;
	} 
	if (right_head) {
		right_head-> left = root;
		root->right = right_head;
	}
	return left_head ? left_head : root;
}

int PrintList(TreeNode* head) {
	while(head) {
		cout << head->value << "->";
		head = head -> right;
	}
	cout << endl;
	return -1;
}

int main() {
    TreeNode* root;
	BuildTree(root);

	TreeNode* head = tree2list(root);
	PrintList(head);
	return -1;
}
