#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

class Node {
  public:
		  Node(int value): value(value), left(NULL), right(NULL) {
		  }
		  int value;
		  Node* left;
		  Node* right;
};

void BuildTree(Node*& root) {
    Node* a = new Node(1);
    Node* b = new Node(2);
    Node* c = new Node(3);
    Node* d = new Node(4);
    Node* e = new Node(5);
    Node* f = new Node(6);
	a->left = b;  a->right = c;
	b->left = d;  b->right = e;
	c->right = f;
	root = a;
}

void PrintTreeByLay(Node* root) {
    queue<Node*> q;
    q.push(root);	
	int first = 1, second = 0;
    while(!q.empty()) {
		Node* tmp = q.front();
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

void PreOrderNo(Node* root) {
     if(root == NULL) return;

     stack<Node*> s;
	 s.push(root);
	 while(!s.empty()) {
	 	Node* p = s.top();
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

void MiddleOrderNo(Node* root)  {  
    if (root == NULL)  return;  
    Node* p = root;  
    stack<Node*> s;  
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

void PostOrderNo(Node *root) {
    if(root == NULL) return;

    stack<Node *> s;
    s.push(root);
    Node *last = root;
    while (!s.empty()) {
        Node* p = s.top();
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

void PreOrder(Node* root) {
	if(root) {
	   cout << root->value <<endl;
	   PreOrder(root->left);
	   PreOrder(root->right);
	}
}

void PostOrder(Node* root) {
	if(root) {
	   PostOrder(root->left);
	   PostOrder(root->right);
	   cout << root->value <<endl;
	}
}

void MiddleOrder(Node* root) {
	if (root) {
	   MiddleOrder(root->left);
	   cout << root->value <<endl;
	   MiddleOrder(root->right);
	}
}

int main () {
    Node* root;
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
	PreOrderNo(root);
	cout << "---------" << endl;
    //
    cout << "PostOrder" << endl;
    PostOrder(root);
    cout << "----------" << endl;
	// 
	cout << "PostOrderNo" << endl;
    PostOrderNo(root);
    cout << "----------" << endl;
    //
    cout << "MiddleOrder" << endl;
    MiddleOrder(root);
    cout << "----------" << endl;
	// 
	cout << "MiddleOrderNo" << endl;
    MiddleOrderNo(root);
    cout << "----------" << endl;
	// 
	return -1;
}
