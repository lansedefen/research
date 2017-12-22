#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Node {
  public:
      int val;
      Node* left;
      Node* right;
      Node(int val) {
          this->val = val;
          this->left = NULL;
          this->right = NULL;
      };
};

bool search(Node* root, int val, Node** p) {
     while(root) {
         int tmp = root->val;
         if(tmp == val) {
            return true;
         }

         *p = root;
         if (val < tmp) {
            root = root->left;
         }
         else {
            root = root->right;
         }
        }
     return false;
}

void inseart(Node* root, int val) {
     Node* p = NULL;
     if(!search(root, val, &p)) {
         Node* tmp = new Node(val);
         if (p->val > val) {
            p->left = tmp;
         }
         else {
            p->right = tmp;
         }
     }
}

void tree_delete(Node* root, int val) {
     Node* p = NULL;
     if(search(root, val, &p)) {
        if(p->left == NULL && p->right == NULL) {
             
        }
        else if (p->left == NULL || p->right == NULL) {

        }
        else {

        }
        cout << p->val << endl;
     }
     return;
}

void print_tree(Node* root) {
     queue<Node*> tmp;
     tmp.push(root);
     int first=1;
     int second = 0;
     while(!tmp.empty()) {
        Node* top_node = tmp.front();
        tmp.pop();
        first -=1;
        cout << top_node->val;

        if(top_node->left) {
           tmp.push(top_node->left);
           second +=1;
        }

        if(top_node->right) {
           tmp.push(top_node->right);
           second +=1;
        }

        if(first == 0) {
          cout << "----------" << first << "," << second << endl;
          first = second;
          second = 0;
        }
     }
}

int main() {
    Node* root = new Node(5);
    inseart(root, 3);
    inseart(root, 6);
    inseart(root, 2);
    inseart(root, 2);
    inseart(root, 4);
    inseart(root, 1);
    print_tree(root);
    tree_delete(root, 5);
}
