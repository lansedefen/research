#include<iostream>

using namespace std;

class ListNode {
  public:
    ListNode(int value):value(value), next(NULL) {
    };
    int value;
    ListNode* next;
};

int CreateList(ListNode** head);
int PrintList(ListNode* head); 

int CreateList(ListNode** head, vector<int> input_array) {
    *head = NULL;
    for(int i = input_array.size() -1; i>=0; i--) {
        ListNode* tmp = new ListNode(input_array[i]);
        tmp->next = *head;
        *head = tmp;
    }
    return -1;
}

int PrintList(ListNode* head) {
    while(head) {
        cout << head->value << "-> ";
        head = head -> next;
    }
    cout << endl;
    return -1;
}
