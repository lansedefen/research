#include<iostream>
#include<vector>
#include<queue>
#include"../tree/tree_head.h"

using namespace std;

bool SearchBinaryTree(TreeNode* root, int target, TreeNode* &p) {
     while(root) {
         int tmp = root->value;
         if(tmp == target) {
            return true;
         }

         p = root;
         if (target < tmp) {
            root = root->left;
         }
         else {
            root = root->right;
         }
        }
     return false;
}

void InsertBinaryTree(TreeNode* root, int val) {
     TreeNode* p = NULL;
     if(!SearchBinaryTree(root, val, p)) {
         TreeNode* tmp = new TreeNode(val);
         if (p->value > val) {
            p->left = tmp;
         }
         else {
            p->right = tmp;
         }
     }
}

void DeleteNode(TreeNode* &p) {
     cout << "delete TreeNode:" << p->value << endl;

     TreeNode* q = p;
     if (!p->left) {
	     p = p->left;
	     delete q;
     } else if(!p->right)  {
	     p = p->right;
	     delete q;
     } 
     else {
        TreeNode* s = p->left;
        while(s->right) {
	      s = s->right;
        }
        s->right = p->right;
        p = p->left;
     }
}

void Remove2(TreeNode* root, int target) {
    TreeNode** t= &root; 
    if(*t) {
        int tmp = (*t)->value;
        if(target < tmp) {
            *t = (*t)->left;
        }
        else if(target > tmp) {
            *t = (*t) -> right;
        }
        else {
            DeleteNode(t);
        }
    }
}

void Remove3(TreeNode* root, int target) {
    TreeNode* t= root; 
    TreeNode* q= NULL; 
    if(t) {
        int tmp = t->value;
        q = t;
        if(target < tmp) {
            t = t->left;
        }
        else if(target > tmp) {
            t = t -> right;
        }
        else {
            DeleteNode(t);
        }
    }
}

void Remove(TreeNode* &t, int target) {
    if(t) {
        if(target < t-> value) {
            Remove(t->left, target);
        }
        else if(target > t-> value)
        {
            Remove(t->right, target);
        }
        else {
            DeleteNode(t);
        }
    }
}

int main() {
    TreeNode* root = new TreeNode(5);
    InsertBinaryTree(root, 3);
    InsertBinaryTree(root, 6);
    InsertBinaryTree(root, 2);
    InsertBinaryTree(root, 2);
    InsertBinaryTree(root, 4);
    InsertBinaryTree(root, 1);
    PrintTree(root);

    TreeNode* new_root = root;
    Remove2(new_root, 5);
    PrintTree(new_root);
    return -1;
}

