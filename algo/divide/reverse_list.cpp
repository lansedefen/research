#include<iostream>
#include<vector>
#include"../list/list_head.h"

using namespace std;

ListNode* ReverseListRecur(ListNode* head) {
	if(!head || !head -> next ) {
		return head;
	}

	ListNode* next_node = head -> next;
	ListNode* new_head = ReverseListRecur(next_node); 
	next_node -> next = head;
	head->next = NULL;
	return new_head;
}

int main() {
    int a[5] = {1,2,3,4,5};
    vector<int> input_array(a, a+4);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);

    ListNode* new_head = ReverseListRecur(head);
    PrintList(new_head);
	return -1;
}
