#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include"tree_head.h"

using namespace std;

void PrintTreeByLay(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);	
	int first = 1, second = 0;
    while(!q.empty()) {
		TreeNode* tmp = q.front();
        cout << tmp->value << ", ";
	    q.pop();
		first -=1;
		if(tmp->left) {
		   second +=1;
		   q.push(tmp->left);
		}	
        if (tmp->right) {
		   second +=1;
		   q.push(tmp->right);
		}
     	if( 0 == first) {
		    first = second;
			cout << endl;
		}
	}
	cout << endl;
}

void PreOrderRecu(TreeNode* root) {
     if(root == NULL) return;

     stack<TreeNode*> s;
	 s.push(root);
	 while(!s.empty()) {
	 	TreeNode* p = s.top();
		cout << p->value << ", ";
		s.pop();
		if(p->right) {
	    	s.push(p->right);
		}
		if(p->left) {
		    s.push(p->left);
		}
	 }
	 cout << endl;
}

void MiddleOrderRecu(TreeNode* root)  {  
    if (root == NULL)  return;  
    TreeNode* p = root;  
    stack<TreeNode*> s;  
    while (!s.empty() || p)  
    {  
        if (p)  {  
            s.push(p);  
            p = p->left;  
        }  
        else  {  
            p = s.top();  
            s.pop();  
            cout << p->value << ", ";  
            p = p->right;  
        }  
    } 
    cout << endl;	
}  

void PostOrderRecu(TreeNode *root) {
    if(root == NULL) return;

    stack<TreeNode *> s;
    s.push(root);
    TreeNode *last = root;
    while (!s.empty()) {
        TreeNode* p = s.top();
        if( (p->left == NULL && p->right == NULL) 
           || (p->right == NULL && last == p->left) 
           || (last == p->right) ) {
			cout << p->value <<", ";
            last = p;
            s.pop();
        }
        else {
            if(p->right)
                s.push(p->right);
            if(p->left)
                s.push(p->left);
        }
    }
	cout << endl;
}

void PreOrder(TreeNode* root) {
	if(root) {
	   cout << root->value <<endl;
	   PreOrder(root->left);
	   PreOrder(root->right);
	}
}

void PostOrder(TreeNode* root) {
	if(root) {
	   PostOrder(root->left);
	   PostOrder(root->right);
	   cout << root->value <<endl;
	}
}

void MiddleOrder(TreeNode* root) {
	if (root) {
	   MiddleOrder(root->left);
	   cout << root->value <<endl;
	   MiddleOrder(root->right);
	}
}

int main () {
    TreeNode* root;
	BuildTree(root);
	// 
	cout << "LayOrder" << endl;
	PrintTreeByLay(root);
	cout << "---------" << endl;
	// 
	cout << "PreOder" << endl;
	PreOrder(root);
	cout << "---------" << endl;
	// 
	cout << "PreOderNo" << endl;
	PreOrderRecu(root);
	cout << "---------" << endl;
    //
    cout << "PostOrder" << endl;
    PostOrder(root);
    cout << "----------" << endl;
	// 
	cout << "PostOrderRecu" << endl;
    PostOrderRecu(root);
    cout << "----------" << endl;
    //
    cout << "MiddleOrder" << endl;
    MiddleOrder(root);
    cout << "----------" << endl;
	// 
	cout << "MiddleOrderRecu" << endl;
    MiddleOrderRecu(root);
    cout << "----------" << endl;
	// 
	return -1;
}
