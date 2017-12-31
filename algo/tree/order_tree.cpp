#include<iostream>
#include<vector>
#include<queue>

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
	a->left = b; 
	a->right = c;
	b->left = d;
	b->right = e;
	c->right = f;
	root = a;
}

void PrintTreeByLay(Node* root) {
    queue<Node*> q;
    q.push(root);	
    while(q.empty()) {
	    
	
	}
}

int main () {
    Node* root;
	BuildTree(root);
	return -1;
}
