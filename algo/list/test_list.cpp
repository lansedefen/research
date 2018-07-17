#include<iostream>
#include<vector>
#include"list_head.h"
#include"remove_list.h"

using namespace std;

ListNode*& removeNode1(ListNode *p) {
    cout << p->value <<endl;
    ListNode*& q = p->next;
    //q = p->next->next;
    return q; 

    /*
    if(p->next != NULL) {
        q = p;
        p = p->next;
        cout << p -> value << endl;
        delete q;
    }*/
}

int main() {
    int a[5] = {1,2,3,4,5};
    vector<int> input_array(a, a+5);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);
    ListNode*& q = removeNode1(head);
    q = q->next;
    PrintList(head);

    /*ListNode* end = GetListEnd(head);
    cout << end->value << endl;
    ListNode* middle = GetListMiddle(head);
    cout << middle->value << endl;

    PartList(head, end);
    */

    return -1;    
}
