#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include"tree_head.h"

using namespace std;

void PrintTreeByLay(TreeNode* root) {
    if (root == NULL) {
        return;
    }

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
     if(root == NULL) 
        return;

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

void PostOrderRecu(TreeNode *root) {
    if(root == NULL) 
        return;

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

void PrevOrderNon(TreeNode* root)    //非递归--前序
{
    if(root == NULL) {
        return ;
    }

    stack<TreeNode*> s;
    TreeNode* cur = root;
    while(cur || !s.empty()) {
        while (cur) {
            cout << cur->value << " ";
            s.push(cur);
            cur = cur->left;
        }

        TreeNode* top = s.top();
        s.pop();
        cur = top->right;  //访问当前根节点的右子树
    }
    cout<<endl;
}

void InOrderNon(TreeNode* root)      //非递归--中序
{
    if(root == NULL)
        return;

    stack<TreeNode*> s;
    TreeNode* cur = root;
    while(cur || !s.empty()) {
        while(cur)
        {
            s.push(cur);
            cur = cur->left;
        }

        TreeNode* top = s.top();    //此时栈顶存的是当前子树的根节点
        cout<<top->value<<" ";
        s.pop();
        cur = top->right;  //将右子树作äB
    }
    cout << endl;
}

void PostOrderNon(TreeNode* root)    //非递归--后序
{
    if (root == NULL) {
        return;
    }

    stack<TreeNode*> s;
    TreeNode* cur = root;
    TreeNode* pos = root;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        TreeNode* top = s.top();
        //top存的是当前的根节点，当top的右子树为空或者top的右子树为pos，说明右子树已经遍历过，
        //这时就可以访问当前的根节点了
        if (top->right == NULL || top->right == pos) {
            cout<<top->value<<" ";
            pos = top;
            s.pop();
        }
        else {
            cur = top->right;
        }
    }
    cout<<endl;
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
	cout << "MiddleOder" << endl;
	MiddleOrder(root);
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

    cout << "new:" << endl;    
    PrevOrderNon(root);
    InOrderNon(root);
    PostOrderNon(root);
	return -1;
}
