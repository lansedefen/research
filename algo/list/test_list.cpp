#include<iostream>
#include<vector>
#include"list_head.h"
#include"remove_list.h"

using namespace std;

int main() {
    int a[5] = {1,2,3,2,5};
    vector<int> input_array(a, a+5);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);
    DeleteListNode(head, 5);
    PrintList(head);

    /*ListNode* end = GetListEnd(head);
    cout << end->value << endl;
    ListNode* middle = GetListMiddle(head);
    cout << middle->value << endl;

    PartList(head, end);
    */

    return -1;    
}
