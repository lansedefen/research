#include<iostream>
#include<vector>
#include"list_head.h"
#include"remove_list.h"
#include"rotate_list.h"

using namespace std;

int main() {
    int a[5] = {4,2,3,6,5};
    vector<int> input_array(a, a+5);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);

	ListNode* new_head = RotateList(head, 2);
    PrintList(new_head);
    //DeleteListNode(head, 5);
    //PrintList(head);

    //ListNode* end = GetListEnd(head);
    //ListNode* new_head = PartList(head, NULL);
    //PrintList(new_head);

    return -1;    
}
