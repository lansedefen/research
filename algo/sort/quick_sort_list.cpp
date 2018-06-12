#include<iostream>
#include<vector>

using namespace std;

class Node {
  public:
    int data;
    Node* next;
    Node(int data) {
        this->data = data;
    };
};

void sort_list(Node* head, Node* left, Node* right, Node* mid) {
    int base = head->data;
    cout << "base:" << base << endl;
    left = head;
    right = left->next;
    while(right) {
        if(base >= right->data) {
            left = left->next;
            int tmp = right->data;
            right->data = left->data;
            left->data = tmp;
        }   
        right = right->next;
    }
    head->data = left->data;
    left->data = base;
}

int main() {
    Node* head = new Node(2);
    Node* a = new Node(1);
    Node* b = new Node(5);
    Node* c = new Node(3);
    Node* d = new Node(-4);
    head->next = a;
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = NULL;
    Node* p = head;

    while(p) {
       cout << p->data << endl;
       p=p->next;
    }

    Node* left;
    Node* right;
    Node* mid;
    sort_list(head, left, right, mid);
    p = head;

    while(p) {
       cout << p->data << endl;
       p=p->next;
    }
 
}
