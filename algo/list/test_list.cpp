#include<iostream>
#include<vector>
#include"list_head.h"
#include"remove_list.h"

using namespace std;

void move(ListNode* &p) {
    p = p->next;
}

void RemoveNode2(ListNode* &p, int value) {
    if (!p) {
        return;
    }

    if (p->value == value) {
        move(p);
        return;
    }

    ListNode* q = p;
    while(q) {
        if(q->next->value == value ) {
                move(q->next);
                break;
        } 
        q = q->next;
    }
}

int main() {
    int a[5] = {1,2,3,4,5};
    vector<int> input_array(a, a+5);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);
    RemoveNode2(head, 2);

    PrintList(head);

    /*ListNode* end = GetListEnd(head);
    cout << end->value << endl;
    ListNode* middle = GetListMiddle(head);
    cout << middle->value << endl;

    PartList(head, end);
    */

    return -1;    
}
