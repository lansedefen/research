#include<iostream>
#include<vector>
#include"list_head.h"

using namespace std;

ListNode* PartList(ListNode* start, ListNode* end) {
    ListNode* index = start;
    while(start != end) {
        start = start->next;
        cout << start-> value;
    }
    return start;
}

int main() {
    int a[5] = {1,2,3,4,5};
    vector<int> input_array(a, a+4);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);

    ListNode* new_head = PartList(head, head->next->next->next);
    PrintList(new_head);
    return -1;    
}
